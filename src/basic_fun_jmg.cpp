/***************************************************************************
                          basic_fun_jmg.cpp  -  basic GDL library function
                             -------------------
    begin                : 2004
    copyright            : (C) 2004 by Joel Gales
    email                : jomoga@users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "includefirst.hpp"

#include <string>
#include <fstream>
#include <memory>
#include <sys/stat.h>

#include "datatypes.hpp"
#include "envt.hpp"
#include "basic_fun.hpp"
#include "io.hpp"
#include "dinterpreter.hpp"
#include "objects.hpp"
#include "basic_fun_jmg.hpp"


//#define GDL_DEBUG
#undef GDL_DEBUG

namespace lib {

  using namespace std;
  using namespace antlr;
 
  
  BaseGDL* size( EnvT* e) 
  {
    static int L64Ix = e->KeywordIx( "L64");
    static int dimIx = e->KeywordIx( "DIMENSIONS");
    static int FILE_LUNIx = e->KeywordIx( "FILE_LUN");
    static int N_DIMENSIONSIx = e->KeywordIx( "N_DIMENSIONS");
    static int N_ELEMENTSIx = e->KeywordIx( "N_ELEMENTS");
    static int STRUCTUREIx = e->KeywordIx( "STRUCTURE");
    static int TNAMEIx = e->KeywordIx( "TNAME");
    static int TYPEIx = e->KeywordIx( "TYPE");

    e->NParam( 1); // might be GDL_UNDEF, but must be given

    // BaseGDL* p0 = e->GetParDefined( 0); //, "SIZE");
    BaseGDL* p0 = e->GetPar( 0); //, "SIZE");

    SizeT nEl = 0;
    SizeT Rank = 0;
    SizeT vType = GDL_UNDEF;

    if (p0 != NULL) {
      nEl = p0->N_Elements();
      Rank = p0->Rank();
      vType = p0->Type();
    }

    // DIMENSIONS
    if( e->KeywordSet( dimIx)) { 
      if( Rank == 0) {
	if( e->KeywordSet(L64Ix))
	  return new DLong64GDL( 0);
	else
	  return new DLongGDL( 0);
      }
      dimension dim( Rank);

      if( e->KeywordSet(L64Ix)) { // L64
	DLong64GDL* res = new DLong64GDL( dim, BaseGDL::NOZERO);
	(*res)[0] = 0;
	for( SizeT i=0; i<Rank; ++i) (*res)[ i] = p0->Dim(i);
	return res;
      } else {
	DLongGDL* res = new DLongGDL( dim, BaseGDL::NOZERO);
	(*res)[0] = 0;
	for( SizeT i=0; i<Rank; ++i) (*res)[ i] = p0->Dim(i);
	return res;
      }

    // FILE_LUN
    } else if( e->KeywordSet(FILE_LUNIx)) { 

      e->Throw( "FILE_LUN not supported yet.");

    // N_DIMENSIONS
    } else if( e->KeywordSet(N_DIMENSIONSIx)) { 

      return new DLongGDL( Rank);

    //N_ELEMENTS
    } else if( e->KeywordSet(N_ELEMENTSIx)) { 

      if( e->KeywordSet(0))
	return new DULongGDL( nEl);
      else
	return new DLongGDL( nEl);

    // STRUCTURE
    } else if( e->KeywordSet(STRUCTUREIx)) { 


      DStructGDL* res = new DStructGDL( "IDL_SIZE");
      if ( p0 == NULL) return res;

      DString tname;
      DString sname;
      if (vType == GDL_STRUCT) {
	tname = "STRUCT";
	DStructGDL* s = static_cast<DStructGDL*>( p0);
	if (s->Desc()->IsUnnamed())
	  sname = "";
	else
	  sname = s->Desc()->Name();
      } else {
	tname = p0->TypeStr();
	sname = "";
      }


      DLongGDL *dims_res = new DLongGDL(dimension(MAXRANK), BaseGDL::ZERO);      

      // Initialize dimension values to 0
      for( SizeT i=Rank; i<MAXRANK; ++i) (*dims_res)[ i] = 0;
      for( SizeT i=0; i<Rank; ++i) {
	(*dims_res)[ i] = p0->Dim(i);
      }

      res->InitTag("TYPE_NAME", DStringGDL(tname));
      res->InitTag("STRUCTURE_NAME", DStringGDL(sname));
      res->InitTag("TYPE", DIntGDL(vType));
      res->InitTag("FILE_LUN", DIntGDL(0));
      res->InitTag("FILE_OFFSET", DLongGDL(0));
      res->InitTag("N_ELEMENTS",  DLongGDL(nEl));
      res->InitTag("N_DIMENSIONS",  DLongGDL(Rank));
      res->InitTag("DIMENSIONS",  *dims_res);

      return res;
      //e->Throw( "STRUCTURE not supported yet.");

    // TNAME
    } else if( e->KeywordSet(TNAMEIx)) { 

      if( p0 == NULL)
	return new DStringGDL( "UNDEFINED");

      return new DStringGDL( p0->TypeStr());

    // TYPE
    } else if( e->KeywordSet(TYPEIx)) { 

      return new DLongGDL( vType );

    } else {

      dimension dim( 3 + Rank);

      if( e->KeywordSet(L64Ix)) {
	DLong64GDL* res = new DLong64GDL( dim, BaseGDL::NOZERO);
	(*res)[ 0] = Rank;
	for( SizeT i=0; i<Rank; ++i) (*res)[ i+1] = p0->Dim(i);
	(*res) [ Rank+1] = vType;
	(*res) [ Rank+2] = nEl;

	return res;
      } else {
	DLongGDL* res = new DLongGDL( dim, BaseGDL::NOZERO);
	(*res)[ 0] = Rank;
	for( SizeT i=0; i<Rank; ++i) (*res)[ i+1] = p0->Dim(i);
	(*res) [ Rank+1] = vType;
	(*res) [ Rank+2] = nEl;

	return res;
      }
    }
    return new DIntGDL( 0); // default for not supported
  }

  BaseGDL* fstat( EnvT* e) 
  { 
    e->NParam( 1);//, "FSTAT");

    DLong lun;
    e->AssureLongScalarPar( 0, lun);

    if( lun < -2 || lun > maxLun)
      throw GDLException( e->CallingNode(), 
			  " File unit is not within allowed range.");

    SizeT size;
    bool big = false;

    if (lun > 0)
    {
      if(fileUnits[ lun-1].IsOpen())  {
	size = fileUnits[ lun-1].Size();
	big = (DLong(size) != size);
      }
    }

    DStructGDL* fstat;
    if (big) fstat = new DStructGDL( "FSTAT64");
    else fstat = new DStructGDL( "FSTAT");
   
    fstat->InitTag("UNIT", DLongGDL( lun));

    if( lun == -2)
      {
	fstat->InitTag("NAME", DStringGDL( "<stderr>"));
	// fstat->InitTag("SIZE", DLongGDL( 0)); 
	fstat->InitTag("OPEN", DByteGDL( 1)); 
	fstat->InitTag("ISATTY", DByteGDL( 1)); 
	// fstat->InitTag("ISAGUI", DByteGDL( 0)); 
	fstat->InitTag("INTERACTIVE", DByteGDL( 1)); 
	// fstat->InitTag("XDR", DByteGDL( 0)); 
	// fstat->InitTag("COMPRESS", DByteGDL( 0)); 
	// fstat->InitTag("READ", DByteGDL( 0)); 
	fstat->InitTag("WRITE", DByteGDL( 1)); 
      }
    else if( lun == -1)
      {
	fstat->InitTag("NAME", DStringGDL( "<stdout>"));
	// fstat->InitTag("SIZE", DLongGDL( 0)); 
	fstat->InitTag("OPEN", DByteGDL( 1)); 
	fstat->InitTag("ISATTY", DByteGDL( 1)); 
	// fstat->InitTag("ISAGUI", DByteGDL( 0)); 
	fstat->InitTag("INTERACTIVE", DByteGDL( 1)); 
	// fstat->InitTag("XDR", DByteGDL( 0)); 
	// fstat->InitTag("COMPRESS", DByteGDL( 0)); 
	// fstat->InitTag("READ", DByteGDL( 0)); 
	fstat->InitTag("WRITE", DByteGDL( 1)); 
      }
    else if( lun == 0)
      {
	fstat->InitTag("NAME", DStringGDL( "<stdin>"));
	// fstat->InitTag("SIZE", DLongGDL( 0)); 
	fstat->InitTag("OPEN", DByteGDL( 1)); 
	fstat->InitTag("ISATTY", DByteGDL( 1)); 
	// fstat->InitTag("ISAGUI", DByteGDL( 0)); 
	fstat->InitTag("INTERACTIVE", DByteGDL( 1)); 
	// fstat->InitTag("XDR", DByteGDL( 0)); 
	// fstat->InitTag("COMPRESS", DByteGDL( 0)); 
	fstat->InitTag("READ", DByteGDL( 1)); 
	// fstat->InitTag("WRITE", DByteGDL( 0)); 
      }
    else
      { // normal file
	GDLStream& actUnit = fileUnits[ lun-1];

	if( !actUnit.IsOpen()) 
	  return fstat; // OPEN tag is init to zero (SpDByte::GetInstance())

	struct stat buffer;
	int status = stat(actUnit.Name().c_str(), &buffer);

	fstat->InitTag("NAME", DStringGDL( actUnit.Name()));
	if (big) fstat->InitTag("SIZE", DLong64GDL( buffer.st_size));//size)); 
        else fstat->InitTag("SIZE", DLongGDL( buffer.st_size));//size));
	fstat->InitTag("OPEN", DByteGDL( 1)); 
	// fstat->InitTag("ISATTY", DByteGDL( 0)); 
	// fstat->InitTag("ISAGUI", DByteGDL( 0)); 
	// fstat->InitTag("INTERACTIVE", DByteGDL( 0)); 
	// fstat->InitTag("COMPRESS", DByteGDL( 0)); 

	fstat->InitTag("COMPRESS",DByteGDL( actUnit.Compress()));

	fstat->InitTag("READ", DByteGDL( actUnit.IsReadable()?1:0)); 
	fstat->InitTag("WRITE", DByteGDL( actUnit.IsWriteable()?1:0)); 
	fstat->InitTag("ATIME", DLong64GDL( buffer.st_atime)); 
	fstat->InitTag("CTIME", DLong64GDL( buffer.st_ctime)); 
	fstat->InitTag("MTIME", DLong64GDL( buffer.st_mtime)); 
        if (big) fstat->InitTag("CUR_PTR", DLong64GDL( actUnit.Tell()));
        else fstat->InitTag("CUR_PTR", DLongGDL( actUnit.Tell()));
      }

    return fstat;
  }
  
  template< typename T>
  BaseGDL* make_array_template( EnvT* e, DLongGDL* dimKey, BaseGDL* value, bool ignore_indgen = false)
  {
    try{
      if (dimKey != NULL) {
	SizeT ndim = dimKey->N_Elements();
	dimension dim( &(*dimKey)[0], ndim);
	if( value != NULL)
	  {
	    T* v = static_cast<T*>( value);
// 	    T* res = new T(dim, BaseGDL::NOZERO);
// 	    SizeT nEl = dim.N_Elements();
// 	    for( SizeT i=0; i<nEl; ++i)
// 	      (*res)[i] = (*v)[0];
	    T* res = v->New( dim, BaseGDL::INIT);
	    return res;
	  }
	if( e->KeywordSet(0)) return new T(dim, BaseGDL::NOZERO);
	if( e->KeywordSet(2) && !ignore_indgen) return new T(dim, BaseGDL::INDGEN);
	return new T(dim);
      } else {
	dimension dim;
	arr( e, dim);
	if( value != NULL)
	  {
	    T* v = static_cast<T*>( value);
// 	    T* res = new T(dim, BaseGDL::NOZERO);
// 	    SizeT nEl = dim.N_Elements();
// 	    for( SizeT i=0; i<nEl; ++i)
// 	      (*res)[i] = (*v)[0];
	    T* res = v->New( dim, BaseGDL::INIT);
	    return res;
	  }
	if( e->KeywordSet(0)) return new T(dim, BaseGDL::NOZERO);
	if( e->KeywordSet(2) && !ignore_indgen) return new T(dim, BaseGDL::INDGEN);
	return new T(dim);
      } 
    }
    catch( GDLException& ex)
      {
	e->Throw( ex.getMessage());
      }
    assert(false);      
    return NULL;
  }

  BaseGDL* make_array( EnvT* e)
  {
    DLong type=0;
    static int typeIx = e->KeywordIx( "TYPE"); 
    e->AssureLongScalarKWIfPresent( typeIx, type);

    DLongGDL* dimKey=NULL;
    Guard<DLongGDL> dimKey_guard;

    static int sizeix = e->KeywordIx( "SIZE"); 
    static int dimensionix = e->KeywordIx( "DIMENSION"); 
    static int indexix = e->KeywordIx( "INDEX"); 

    BaseGDL* size = e->GetKW(sizeix);
    BaseGDL* b_dimension = e->GetKW(dimensionix);
    if(b_dimension != NULL)
      {
	DLongGDL* l_dimension = e->GetKWAs<DLongGDL>( dimensionix);
	if(e->NParam() == 0 && size == NULL) 
	  {
	    dimension dim(l_dimension->N_Elements(),1);
	    dimKey=new DLongGDL(dim, BaseGDL::NOZERO);
	    dimKey_guard.Reset( dimKey); //e->Guard( dimKey);
	    for (int i=0;i<l_dimension->N_Elements();++i)
	      (*dimKey)[i]=(*l_dimension)[i];
	  }
	  
      } 
    else if(size != NULL)
      {
	DLongGDL* l_size = e->GetKWAs<DLongGDL>( sizeix);
	if( l_size->N_Elements() < 4 || l_size->N_Elements() > 11)
	  e->Throw("Keyword array parameter SIZE must have from "
		   "4 to 11 elements.");
	type=(*l_size)[(*l_size)[0]+1];
	if(e->NParam() == 0) 
	  {
	    dimension dim((*l_size)[0],1);
	    dimKey=new DLongGDL(dim, BaseGDL::NOZERO);
	    dimKey_guard.Reset( dimKey); //e->Guard( dimKey);
	    //	    e->Guard( dimKey);
	    for (int i=1;i<=(*l_size)[0];++i)
	      (*dimKey)[i-1]=(*l_size)[i];
	  }
	    
      }

    if( type < 0 || type > GDL_ULONG64 || type == GDL_STRUCT)
      {
	e->Throw("Invalid type specified for result.");
      }
 
// TODO: sanity check on dimKey & arguments - if all are > 0, otherwise:
//       e->Throw("Array dimensions must be greater than 0.");

    if (e->KeywordSet(indexix))
    {
      if (type == GDL_PTR || e->KeywordSet(18)) 
        e->Throw("Index initialization of pointer array is invalid.");
      if (type == GDL_OBJ || e->KeywordSet(19)) 
        e->Throw("Index initialization of object reference array is invalid..");
    }

    static int valueix = e->KeywordIx( "VALUE"); 
    BaseGDL* value = e->GetKW( valueix);
    Guard<BaseGDL> value_guard;
    if( value != NULL)
      {
	if( !value->Scalar())
	  e->Throw("Keyword must be a scalar in this context: "+
		   e->GetString(valueix));
	if( type == 0)
	  type = value->Type();
	else
	  {
	    value = value->Convert2( static_cast<DType>(type), BaseGDL::COPY);
	    value_guard.Reset(value);//e->Guard( value);
	  }
      }

    // BYTEDComplexDblGDL
    if (e->KeywordSet(6) || type == GDL_BYTE) {

      return make_array_template< DByteGDL>( e, dimKey, value);

      //GDL_INT
    } else if (e->KeywordSet(7) || type == GDL_INT) {

      return make_array_template< DIntGDL>( e, dimKey, value);

      // GDL_UINT
    } else if (e->KeywordSet(8) || type == GDL_UINT) {

      return make_array_template< DUIntGDL>( e, dimKey, value);

      // GDL_LONG
    } else if (e->KeywordSet(9) || type == GDL_LONG) {

      return make_array_template< DLongGDL>( e, dimKey, value);

      // GDL_ULONG
    } else if (e->KeywordSet(10) || type == GDL_ULONG) {

      return make_array_template< DULongGDL>( e, dimKey, value);

      // GDL_LONG64
    } else if (e->KeywordSet(11) || type == GDL_LONG64) {

      return make_array_template< DLong64GDL>( e, dimKey, value);

      // GDL_ULONG64
    } else if (e->KeywordSet(12) || type == GDL_ULONG64) {

      return make_array_template< DULong64GDL>( e, dimKey, value);
      
      // GDL_DOUBLE
    } else if (e->KeywordSet(14) || type == GDL_DOUBLE) {

      return make_array_template< DDoubleGDL>( e, dimKey, value);

      // GDL_COMPLEX
    } else if (e->KeywordSet(15) || type == GDL_COMPLEX) {

      return make_array_template< DComplexGDL>( e, dimKey, value);

      // DCOMPLEX
    } else if (e->KeywordSet(16) || type == GDL_COMPLEXDBL) {

      return make_array_template< DComplexDblGDL>( e, dimKey, value);

      // GDL_STRING (added by MS 29.10.2005)
    } else if (e->KeywordSet(17) || type == GDL_STRING) {

      if (!e->KeywordSet(indexix))
		return make_array_template< DStringGDL>( e, dimKey, value);
      
      // 'true' for ignoring /INDEX keyword 
	 // BaseGDL* ret = make_array_template< DStringGDL>( e, dimKey, value, true);
//       if (e->KeywordSet(indexix))
//       {

	  BaseGDL* ret = make_array_template< DULongGDL>( e, dimKey, value); //, true);
      return ret->Convert2( GDL_STRING);

//         for (DLong i = 0; i < ret->N_Elements(); ++i)
//         {
//           char tmp[13];
//           assert(sprintf(tmp, "%12d", i) == 12);
//           (*static_cast<DStringGDL*>(ret))[i] = tmp;
//         }
//       }
//       return ret;

      // GDL_PTR (added by SA 15.08.2009)
    } else if (e->KeywordSet(18) || type == GDL_PTR) {

      return make_array_template< DPtrGDL>( e, dimKey, value);

      // OBJ (added by SA 15.08.2009)
    } else if (e->KeywordSet(19) || type == GDL_OBJ) {

      return make_array_template< DObjGDL>( e, dimKey, value);

      // GDL_STRUCT
    } else if ( type == GDL_STRUCT) {
      
      assert( value != NULL);

      DStructGDL* v = static_cast<DStructGDL*>( value);
      if (dimKey != NULL) {
	SizeT ndim = dimKey->N_Elements();
	dimension dim((DLong *) &(*dimKey)[0], (SizeT) ndim);
	return v->New( dim, BaseGDL::INIT);
      } else {
	dimension dim;
	arr( e, dim);
	return v->New( dim, BaseGDL::INIT);
      } 
    } else {
      return make_array_template< DFloatGDL>( e, dimKey, value);
    }
    return 0;
  }


  
  BaseGDL* reform( EnvT* e)
  {
    SizeT nParam=e->NParam(1);

    BaseGDL** p0P = &e->GetParDefined( 0);
    BaseGDL* p0 = *p0P;

    SizeT nEl = p0->N_Elements();
//     SizeT Rank = p0->Rank();
//     if( Rank == 0)
//       e->Throw( "Parameter must be an array in this context: " 
// 		+ e->GetParString( 0));

//     SizeT Type = p0->Type();

    dimension dim;

    if (nParam == 1) {
      //      SizeT j=1;
      for( SizeT i=0; i<p0->Rank(); ++i) {
	//	if (p0->Dim(i) == 0) break;
	if (p0->Dim(i) > 1)
	  {
	    dim << p0->Dim( i);  
	  //	  j *= p0->Dim(i);
	  //	  cout << j << p0->Dim(i) << endl;
	  //	  dim.Set(j,p0->Dim(i));
	  //j++;
	  }
      }
      if( dim.Rank() == 0)
	dim << 1;
      //     dim.Set(0, j);
    } 
    else 
      arr( e, dim, 1);

    if (dim.NDimElements() != nEl) 
      e->Throw( "New subscripts must not change the number of elements in " 
		+ e->GetParString( 0));

    // make a copy if p0 is not global
    //      if( !e->GlobalPar( 0))
    //	p0 = p0->Dup();
    // better: steal p0
    if( !e->GlobalPar( 0))
      {
	bool success = e->StealLocalPar( 0); //*p0P = NULL;
	//*p0P = NULL; // prevent local parameter form deletion
	assert( success);
	p0->SetDim(dim);
	return p0;
      }

    static int overwriteIx = e->KeywordIx("OVERWRITE");
    if (e->KeywordSet( overwriteIx)) 
    {
      p0->SetDim(dim);
      e->SetPtrToReturnValue( p0P);
      return p0;
    }

    // global paramter - make a copy
    BaseGDL* res = p0->Dup();
    res->SetDim(dim);
    return res;
  }

  
  // note: changes here MUST be reflected in routine_names_reference() as well
  // because DLibFun of this function is used for routine_names_reference() the keyword
  // indices must match
  BaseGDL* routine_names_value( EnvT* e) 
  {
    SizeT nParam=e->NParam();

    EnvStackT& callStack = e->Interpreter()->CallStack();
//     DLong curlevnum = callStack.size()-1;
	// 'e' is not on the stack
	DLong curlevnum = callStack.size();

    if (e->KeywordSet( "S_FUNCTIONS")) {
      vector<DString> subList;

      SizeT nFun = libFunList.size();
      for( SizeT i = 0; i<nFun; ++i) {
	DString s = libFunList[ i]->ToString();
	s = s.substr(4);  // Remove "res="

	size_t left_paren = s.find_first_of("(");
	subList.push_back( s.substr( 0, left_paren));
      }

      sort( subList.begin(), subList.end());

      DStringGDL* res = new DStringGDL( dimension( nFun), BaseGDL::NOZERO);
      for( SizeT i = 0; i<nFun; ++i) {
	(*res)[i] = subList[ i];
      }
      return res;
    }

    if (e->KeywordSet( "S_PROCEDURES")) {
      vector<DString> subList;

      SizeT nPro = libProList.size();
      for( SizeT i = 0; i<nPro; ++i) {
	DString s = libProList[ i]->ToString();

	size_t comma_brac = s.find_first_of(",[");
	subList.push_back( s.substr( 0, comma_brac));
      }

      sort( subList.begin(), subList.end());

      DStringGDL* res = new DStringGDL( dimension( nPro), BaseGDL::NOZERO);
      for( SizeT i = 0; i<nPro; ++i) {
	(*res)[i] = subList[ i];
      }
      return res;
    }

    if (e->KeywordSet( "LEVEL")) {
      return new DLongGDL( curlevnum );
    }

    static int variablesIx = e->KeywordIx( "VARIABLES" );
    static int fetchIx = e->KeywordIx( "FETCH" );
    static int arg_namesIx = e->KeywordIx( "ARG_NAME" );
    static int storeIx = e->KeywordIx( "STORE" );
    bool var=false, fetch=false, arg=false, store=false;

    DLongGDL* level;
    level = e->IfDefGetKWAs<DLongGDL>( variablesIx);
    if (level != NULL) {
      var = true;
    } else {
      level = e->IfDefGetKWAs<DLongGDL>( fetchIx);
      if (level != NULL) {
	fetch = true;
      } else {
	level = e->IfDefGetKWAs<DLongGDL>( arg_namesIx);
	if (level != NULL) {
	  arg = true;
	} else {
	  level = e->IfDefGetKWAs<DLongGDL>( storeIx);
	  if (level != NULL) {
	    store = true;
	  }
	}
      }
    }

    DString varName;

    if (level != NULL) {
      DLong desiredlevnum = (*level)[0];
      if (desiredlevnum <= 0) desiredlevnum += curlevnum;
      if (desiredlevnum < 1) return new DStringGDL("");
      if (desiredlevnum > curlevnum) desiredlevnum = curlevnum;

      DSubUD* pro = static_cast<DSubUD*>(callStack[desiredlevnum-1]->GetPro());

      SizeT nVar = pro->Size(); // # var in GDL for desired level 
      int nKey = pro->NKey();
      //cout << "nKey:" << nKey << endl;
      //cout << "nVar:" << nVar << endl;
      //cout << pro->Name() << endl;

      if (var) {
	if( nVar == 0) return new DStringGDL("");

	DStringGDL* res = new DStringGDL( dimension( nVar), BaseGDL::NOZERO);
	for( SizeT i = 0; i<nVar; ++i) {
	  string vname = pro->GetVarName( i);
	  (*res)[i] = vname;
	}
	return res;
      } else if (fetch) { // FETCH

	e->AssureScalarPar<DStringGDL>( 0, varName);
	varName = StrUpCase( varName);
	int xI = pro->FindVar( varName);
	//	cout << xI << endl;
	if (xI != -1) {
// 	  BaseGDL* par = ((EnvT*)(callStack[desiredlevnum-1]))->GetPar( xI);
	  BaseGDL*& par = ((EnvT*)(callStack[desiredlevnum-1]))->GetPar( xI);

	  if( par == NULL)
 		e->Throw( "Variable is undefined: " + varName);
// 		return NULL;
	  //	  char* addr = static_cast<char*>(par->DataAddr());

	  // no retnew function BUT: ret value is not from current environment
	  // which is ok with the new ref return value handling introdcuced with 0.9.4
	  // note that the _reference version does not need par to be defined and is hence still necessary
	  e->SetPtrToReturnValue( &par); // <-  HERE IS THE DIFFERENCE
	  return par; // <-  HERE IS THE DIFFERENCE 
	  // return par->Dup(); // <-  HERE IS THE DIFFERENCE // no retnew function BUT: ret value is not from current environment
	}
	
 	e->Throw( "Variable not found: " + varName);
 	return NULL;
      } else if (arg) { // ARG_NAME

	if( nParam == 0) return new DStringGDL("");

	DStringGDL* res = new DStringGDL( dimension( nParam), BaseGDL::NOZERO);

	//	cout << "nVar:" << nVar << endl;
	EnvBaseT* desiredCallStack;
	if( desiredlevnum >= callStack.size())
		desiredCallStack = e;
	else
		desiredCallStack = callStack[ desiredlevnum];
	
// 	SizeT nCall = callStack[desiredlevnum]->NParam();
	SizeT nCall = desiredCallStack->NParam();
	
	//	cout << "nCall:" << nCall << "curlevnum:" << curlevnum << endl;
	for( SizeT i = 0; i<nParam; ++i) {
	  for( SizeT j = 0; j<nCall; ++j) {

	    if (e->GetParString(i) == 
		desiredCallStack->GetParString(j)) {
	      //	      cout << "Calling param: " << j+1 << endl;
	      BaseGDL*& p = e->GetPar( i);
	      if (p == NULL) {
		(*res)[i]="UNDEFINED";
// 		break;
	      }
	      //	      cout << "p:" << p << endl;

	      for( SizeT xI=0; xI<nVar; ++xI) {
		string vname = pro->GetVarName( xI);
		BaseGDL*& par = ((EnvT*)(callStack[desiredlevnum-1]))->
		  GetPar( xI-nKey);

		//    cout << "xI:" << xI << " " << vname.c_str() << endl;
		//    cout << "par:" << par << endl;
		if (&par == &p) {
		  (*res)[i] = vname;
		  break;
		}
	      } // xI loop
	      break;
	    }
	  } // j loop
	} // i loop

	return res;
      } else { // STORE

	if( nParam != 2)
	  throw GDLException( e->CallingNode(),
			      "ROUTINE_NAMES: Incorrect number of arguments.");

	// "res" points to variables to be restored
	BaseGDL* res = e->GetParDefined( 1);

	SizeT s;
	e->AssureScalarPar<DStringGDL>( 0, varName); 
	int xI = pro->FindVar(StrUpCase( varName));
	// cout << "varName: " << StrUpCase( varName) << " xI: " << xI << endl;
	if (xI == -1) {

	  SizeT u = pro->AddVar(StrUpCase(varName));
 	  s = callStack[desiredlevnum-1]->AddEnv();
	  //cout << "AddVar u: " << u << endl;
	  //cout << "AddEnv s: " << s << endl;

	} else {
	  s = xI;
	  //cout << "FindVar s: " << s << endl;
	}

// 	BaseGDL*& par = ((EnvT*)(callStack[desiredlevnum-1]))->GetPar( s-nKey);

 	((EnvT*)(callStack[desiredlevnum-1]))->GetPar( s-nKey) = res->Dup();

	//	cout << "par: " << &par << endl << endl;
// 	memcpy(&par, &res, sizeof(par)); 

	return new DIntGDL( 1);
      }
    } else {
      // Get Compiled Procedures & Functions 
      DLong n = proList.size() + funList.size() + 1;

      // Add $MAIN$ to list
      vector<DString> pfList;
      pfList.push_back("$MAIN$");

      // Procedures
      for( ProListT::iterator i=proList.begin(); i != proList.end(); i++) {
	pfList.push_back((*i)->ObjectName());
      }

      // Functions
      for( FunListT::iterator i=funList.begin(); i != funList.end(); i++) {
	pfList.push_back((*i)->ObjectName());
      }

      // Sort
      sort( pfList.begin(), pfList.end());

      // Fill return variable
      dimension dim(&n, (size_t) 1);
      DStringGDL* res = new DStringGDL(dim, BaseGDL::NOZERO);
      for( SizeT i = 0; i<n; ++i) {
	(*res)[i] = pfList[ i];
      }
      return res;
    }
  }

  // this version does not need the return value pointing to a defined value and is hence necessary  
  BaseGDL** routine_names_reference( EnvT* e) 
  {
    SizeT nParam=e->NParam();

    EnvStackT& callStack = e->Interpreter()->CallStack();
//     DLong curlevnum = callStack.size()-1;
	// 'e' is not on the stack
	DLong curlevnum = callStack.size();

    if (e->KeywordSet( "S_FUNCTIONS")) {
      return NULL;
    }

    if (e->KeywordSet( "S_PROCEDURES")) {
      return NULL;
    }

    if (e->KeywordSet( "LEVEL")) {
      return NULL;
    }

    static int variablesIx = e->KeywordIx( "VARIABLES" );
    static int fetchIx = e->KeywordIx( "FETCH" );
    static int arg_namesIx = e->KeywordIx( "ARG_NAME" );
    static int storeIx = e->KeywordIx( "STORE" );
    bool var=false, fetch=false, arg=false, store=false;

    DLongGDL* level;
    level = e->IfDefGetKWAs<DLongGDL>( variablesIx);
    if (level != NULL) {
      var = true;
    } else {
      level = e->IfDefGetKWAs<DLongGDL>( fetchIx);
      if (level != NULL) {
	fetch = true;
      } else {
	level = e->IfDefGetKWAs<DLongGDL>( arg_namesIx);
	if (level != NULL) {
	  arg = true;
	} else {
	  level = e->IfDefGetKWAs<DLongGDL>( storeIx);
	  if (level != NULL) {
	    store = true;
	  }
	}
      }
    }

    DString varName;

    if (level != NULL) {
      DLong desiredlevnum = (*level)[0];
      if (desiredlevnum <= 0) desiredlevnum += curlevnum;
      if (desiredlevnum < 1) return NULL;
      if (desiredlevnum > curlevnum) desiredlevnum = curlevnum;

      DSubUD* pro = static_cast<DSubUD*>(callStack[desiredlevnum-1]->GetPro());

      SizeT nVar = pro->Size(); // # var in GDL for desired level 
      int nKey = pro->NKey();
      //cout << "nKey:" << nKey << endl;
      //cout << "nVar:" << nVar << endl;
      //cout << pro->Name() << endl;

      if (fetch) { // FETCH

	e->AssureScalarPar<DStringGDL>( 0, varName);
	varName = StrUpCase( varName);
	int xI = pro->FindVar( varName);
	//	cout << xI << endl;
	if (xI != -1) {
	  BaseGDL*& par = ((EnvT*)(callStack[desiredlevnum-1]))->GetPar( xI);
	  return &par; // <-  HERE IS THE DIFFERENCE
	}
	
	e->Throw( "Variable not found: " + varName);
	return NULL;

      } else if (var) { // ARG_NAME

	return NULL;

      } else if (arg) { // ARG_NAME

	return NULL;

      } 
      else { // STORE

	return NULL;
      }
    } 
    else 
    {
	// Get Compiled Procedures & Functions 
	return NULL;
    }
  }

  
  
} // namespace

