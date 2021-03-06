/***************************************************************************
                          objects.cpp  -  global structures
                             -------------------
    begin                : July 22 2002
    copyright            : (C) 2002 by Marc Schellens
    email                : m_schellens@users.sf.net
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

#include <limits>
#include <ios>

#include "str.hpp"
#include "gdlexception.hpp"
#include "initsysvar.hpp"
#include "dnodefactory.hpp"

#include "objects.hpp"
#include "graphicsdevice.hpp"
#include "preferences.hpp"
#include "overload.hpp"

//#include "dinterpreter.hpp"

#ifdef _OPENMP
#include <omp.h>
#endif

#ifdef HAVE_LIBWXWIDGETS
#include "gdlwidget.hpp"
#endif

#ifdef USE_PYTHON
#include "gdlpython.hpp"
#endif

using namespace std;

// DInterpreter* interpreter = NULL;

// instantiate the global lists
VarListT      sysVarList;
VarListT      sysVarRdOnlyList;

FunListT      funList;
ProListT      proList;

LibFunListT   libFunList;
LibProListT   libProList;

CommonListT   commonList;

StructListT   structList;

GDLFileListT  fileUnits;

// flag for control-c
volatile bool sigControlC;
int           debugMode;

namespace structDesc {
  // set in InitStructs()
  DStructDesc* LIST = NULL;
  DStructDesc* HASH = NULL;
  DStructDesc* GDL_CONTAINER_NODE = NULL;
  DStructDesc* GDL_HASHTABLEENTRY = NULL;
}

// for OpenMP
DLong CpuTPOOL_NTHREADS;
DLong CpuTPOOL_MIN_ELTS;
DLong CpuTPOOL_MAX_ELTS;
const DLong CpuTPOOL_MAX_ELTS_max = numeric_limits<DLong>::max();

// instantiate own AST factory
//_DNodeFactory DNodeFactory;
antlr::ASTFactory DNodeFactory("DNode",DNode::factory);

void ResetObjects()
{
  GraphicsDevice::DestroyDevices();

  fileUnits.clear();
  cerr << flush; cout << flush; clog << flush;

  PurgeContainer(sysVarList);
  PurgeContainer(funList);
  PurgeContainer(proList);
  PurgeContainer(structList); // now deletes member subroutines (and they in turn common block references
  // hence delete common blocks after structList
  PurgeContainer(commonList);
  
  // don't purge library here
//   PurgeContainer(libFunList);
//   PurgeContainer(libProList);
  
#ifdef USE_PYTHON
  PythonEnd();
#endif
}

// initialize struct descriptors which are not system variables
void InitStructs()
{
  SpDInt    aInt;
  SpDLong   aLong;
  SpDString aString;
  SpDByte   aByte;
  SpDULong  aULong;
  SpDLong64 aLong64;
  SpDFloat  aFloat;
  SpDDouble aDouble;
  SpDLong   aLongArr8( dimension(8));
  SpDPtr    aPtrRef;
  SpDObj    aObjRef;

  // OBJECTS =================================================

  DStructDesc* gdl_object = new DStructDesc( GDL_OBJECT_NAME);
  gdl_object->AddTag("GDL_OBJ_TOP", &aLong64);
  gdl_object->AddTag("__OBJ__", &aObjRef);
  gdl_object->AddTag("GDL_OBJ_BOTTOM", &aLong64);
  // special for GDL_OBJECT ony
  gdl_object->InitOperatorList();
  // insert into structList
  structList.push_back(gdl_object);
  
  DStructDesc* gdlList = new DStructDesc( "LIST");
  gdlList->AddTag("GDL_CONTAINER_TOP", &aLong64);
  gdlList->AddTag("GDLCONTAINERVERSION", &aInt);
  gdlList->AddTag("PHEAD", &aPtrRef);
  gdlList->AddTag("PTAIL", &aPtrRef);
  gdlList->AddTag("NLIST", &aLong);
  gdlList->AddTag("GDL_CONTAINER_BOTTOM", &aLong64);
  // use operator overloading (note: gdl_object's operators are not set yet)
  gdlList->AddParent(gdl_object);
  // insert into structList
  structList.push_back(gdlList);
  structDesc::LIST = gdlList;
  
  DStructDesc* gdlContainerNode = new DStructDesc( "GDL_CONTAINER_NODE");
  gdlContainerNode->AddTag("PNEXT", &aPtrRef);
  gdlContainerNode->AddTag("PDATA", &aPtrRef);
//   gdlContainerNode->AddTag("OOBJ", &aObjRef);
//   gdlContainerNode->AddTag("FLAGS", &aLong);
  // insert into structList
  structList.push_back(gdlContainerNode);
  structDesc::GDL_CONTAINER_NODE = gdlContainerNode;

  DStructDesc* gdlHash = new DStructDesc( "HASH");
  gdlHash->AddTag("TABLE_BITS", &aULong);
  gdlHash->AddTag("TABLE_SIZE", &aULong);
  gdlHash->AddTag("TABLE_COUNT", &aULong);
  gdlHash->AddTag("TABLE_REMOVE", &aULong);
  gdlHash->AddTag("TABLE_FOREACH", &aULong);
  gdlHash->AddTag("TABLE_DATA", &aPtrRef);
  // use operator overloading (note: gdl_object's operators are not set yet)
  gdlHash->AddParent(gdl_object);
  // insert into structList
  structList.push_back(gdlHash);
  structDesc::HASH = gdlHash;

  DStructDesc* gdlHashTE = new DStructDesc( "GDL_HASHTABLEENTRY");
  gdlHashTE->AddTag("PKEY", &aPtrRef);
  gdlHashTE->AddTag("PVALUE", &aPtrRef);
  // insert into structList
  structList.push_back(gdlHashTE);
  structDesc::GDL_HASHTABLEENTRY = gdlHashTE;
  
  // OBJECTS END =======================================================

  
  
  DStructDesc* gdl_size = new DStructDesc( "IDL_SIZE");
  gdl_size->AddTag("TYPE_NAME", &aString);
  gdl_size->AddTag("STRUCTURE_NAME", &aString);
  gdl_size->AddTag("TYPE", &aInt);
  gdl_size->AddTag("FILE_LUN", &aInt);
  gdl_size->AddTag("FILE_OFFSET",  &aLong);
  gdl_size->AddTag("N_ELEMENTS",  &aLong);
  gdl_size->AddTag("N_DIMENSIONS",  &aLong);
  gdl_size->AddTag("DIMENSIONS",  &aLongArr8);
  // insert into structList
  structList.push_back(gdl_size);


  for (int big = 1; big >= 0; --big) 
  {
    DStructDesc* fstat = new DStructDesc( big ? "FSTAT64" : "FSTAT");
    fstat->AddTag("UNIT", &aLong);
    fstat->AddTag("NAME", &aString);
    fstat->AddTag("OPEN", &aByte);
    fstat->AddTag("ISATTY", &aByte);
    fstat->AddTag("ISAGUI", &aByte);
    fstat->AddTag("INTERACTIVE", &aByte);
    fstat->AddTag("XDR", &aByte);
    fstat->AddTag("COMPRESS", &aByte);
    fstat->AddTag("READ", &aByte);
    fstat->AddTag("WRITE", &aByte);
    fstat->AddTag("ATIME", &aLong64);
    fstat->AddTag("CTIME", &aLong64);
    fstat->AddTag("MTIME", &aLong64);
    if (big)
    {
      fstat->AddTag("TRANSFER_COUNT", &aLong64);
      fstat->AddTag("CUR_PTR", &aLong64);
      fstat->AddTag("SIZE", &aLong64);
      fstat->AddTag("REC_LEN", &aLong64);
    }
    else
    {
      fstat->AddTag("TRANSFER_COUNT", &aLong);
      fstat->AddTag("CUR_PTR", &aLong);
      fstat->AddTag("SIZE", &aLong);
      fstat->AddTag("REC_LEN", &aLong);
    }
    // insert into structList
    structList.push_back( fstat);
  }

  DStructDesc* finfo = new DStructDesc("FILE_INFO");
  finfo->AddTag("NAME", &aString);
  finfo->AddTag("EXISTS", &aByte);
  finfo->AddTag("READ", &aByte);
  finfo->AddTag("WRITE", &aByte);
  finfo->AddTag("EXECUTE", &aByte);
  finfo->AddTag("REGULAR", &aByte);
  finfo->AddTag("DIRECTORY", &aByte);
  finfo->AddTag("BLOCK_SPECIAL", &aByte);
  finfo->AddTag("CHARACTER_SPECIAL", &aByte);
  finfo->AddTag("NAMED_PIPE", &aByte);
  finfo->AddTag("SETUID", &aByte);
  finfo->AddTag("SETGID", &aByte);
  finfo->AddTag("SOCKET", &aByte);
  finfo->AddTag("STICKY_BIT", &aByte);
  finfo->AddTag("SYMLINK", &aByte);
  finfo->AddTag("DANGLING_SYMLINK", &aByte);
  finfo->AddTag("MODE", &aLong);
  finfo->AddTag("ATIME", &aLong64);
  finfo->AddTag("CTIME", &aLong64);
  finfo->AddTag("MTIME", &aLong64);
  finfo->AddTag("SIZE", &aLong64);
  // insert into structList
  structList.push_back( finfo);

  DStructDesc* memory = new DStructDesc("IDL_MEMORY");
  memory->AddTag("CURRENT", &aLong);
  memory->AddTag("NUM_ALLOC", &aLong);
  memory->AddTag("NUM_FREE", &aLong);
  memory->AddTag("HIGHWATER", &aLong);
  // insert into structList
  structList.push_back(memory);

  DStructDesc* memory64 = new DStructDesc("IDL_MEMORY64");
  memory64->AddTag("CURRENT", &aLong64);
  memory64->AddTag("NUM_ALLOC", &aLong64);
  memory64->AddTag("NUM_FREE", &aLong64);
  memory64->AddTag("HIGHWATER", &aLong64);
  // insert into structList
  structList.push_back(memory64);

  DStructDesc* machar = new DStructDesc( "MACHAR");
  machar->AddTag("IBETA", &aLong);
  machar->AddTag("IT", &aLong);
  machar->AddTag("IRND", &aLong);
  machar->AddTag("NGRD", &aLong);
  machar->AddTag("MACHEP", &aLong);
  machar->AddTag("NEGEP", &aLong);
  machar->AddTag("IEXP", &aLong);
  machar->AddTag("MINEXP", &aLong);
  machar->AddTag("MAXEXP", &aLong);
  machar->AddTag("EPS", &aFloat);
  machar->AddTag("EPSNEG", &aFloat);
  machar->AddTag("XMIN", &aFloat);
  machar->AddTag("XMAX", &aFloat);
  // insert into structList
  structList.push_back( machar);

  DStructDesc* dmachar = new DStructDesc( "DMACHAR");
  dmachar->AddTag("IBETA", &aLong);
  dmachar->AddTag("IT", &aLong);
  dmachar->AddTag("IRND", &aLong);
  dmachar->AddTag("NGRD", &aLong);
  dmachar->AddTag("MACHEP", &aLong);
  dmachar->AddTag("NEGEP", &aLong);
  dmachar->AddTag("IEXP", &aLong);
  dmachar->AddTag("MINEXP", &aLong);
  dmachar->AddTag("MAXEXP", &aLong);
  dmachar->AddTag("EPS", &aDouble);
  dmachar->AddTag("EPSNEG", &aDouble);
  dmachar->AddTag("XMIN", &aDouble);
  dmachar->AddTag("XMAX", &aDouble);
  // insert into structList
  structList.push_back( dmachar);

  // for internal usage
  // attention: $WIDGET_MESSAGE would identify this as an unnamed struct
  // see DStructDesc constructor
  DStructDesc* widgmsg = new DStructDesc( "*WIDGET_MESSAGE*");
  widgmsg->AddTag("ID", &aLong);
  widgmsg->AddTag("TOP", &aLong);
  widgmsg->AddTag("HANDLER", &aLong);
  widgmsg->AddTag("MESSAGE", &aLong);
  // insert into structList
  structList.push_back( widgmsg);

  DStructDesc* widgbut = new DStructDesc( "WIDGET_BUTTON");
  widgbut->AddTag("ID", &aLong);
  widgbut->AddTag("TOP", &aLong);
  widgbut->AddTag("HANDLER", &aLong);
  widgbut->AddTag("SELECT", &aLong);
  // insert into structList
  structList.push_back( widgbut);

  DStructDesc* widgdlist = new DStructDesc( "WIDGET_DROPLIST");
  widgdlist->AddTag("ID", &aLong);
  widgdlist->AddTag("TOP", &aLong);
  widgdlist->AddTag("HANDLER", &aLong);
  widgdlist->AddTag("INDEX", &aLong);
  // insert into structList
  structList.push_back( widgdlist);

  DStructDesc* widgcbox = new DStructDesc( "WIDGET_COMBOBOX");
  widgcbox->AddTag("ID", &aLong);
  widgcbox->AddTag("TOP", &aLong);
  widgcbox->AddTag("HANDLER", &aLong);
  widgcbox->AddTag("INDEX", &aLong);
  widgcbox->AddTag("STR", &aString);
  // insert into structList
  structList.push_back( widgcbox);

  DStructDesc* widglist = new DStructDesc( "WIDGET_LIST");
  widglist->AddTag("ID", &aLong);
  widglist->AddTag("TOP", &aLong);
  widglist->AddTag("HANDLER", &aLong);
  widglist->AddTag("INDEX", &aLong);
  widglist->AddTag("CLICKS", &aLong);
  // insert into structList
  structList.push_back( widglist);

  DStructDesc* widgdtab = new DStructDesc( "WIDGET_TAB");
  widgdtab->AddTag("ID", &aLong);
  widgdtab->AddTag("TOP", &aLong);
  widgdtab->AddTag("HANDLER", &aLong);
  widgdtab->AddTag("TAB", &aLong);
  // insert into structList
  structList.push_back( widgdtab);

  DStructDesc* widgdsl = new DStructDesc( "WIDGET_SLIDER");
  widgdsl->AddTag("ID", &aLong);
  widgdsl->AddTag("TOP", &aLong);
  widgdsl->AddTag("HANDLER", &aLong);
  widgdsl->AddTag("VALUE", &aLong);
  widgdsl->AddTag("DRAG", &aInt);
  // insert into structList
  structList.push_back( widgdsl);

  DStructDesc* widgbgroup =  new DStructDesc( "WIDGET_BGROUP");
  widgbgroup->AddTag("ID", &aLong);
  widgbgroup->AddTag("TOP", &aLong);
  widgbgroup->AddTag("HANDLER", &aLong);
  widgbgroup->AddTag("SELECT", &aLong);
  widgbgroup->AddTag("VALUE", &aLong);
  // insert into structList
  structList.push_back(widgbgroup);

  DStructDesc* widgtxtc = new DStructDesc( "WIDGET_TEXT_CH");
  widgtxtc->AddTag("ID", &aLong);
  widgtxtc->AddTag("TOP", &aLong);
  widgtxtc->AddTag("HANDLER", &aLong);
  widgtxtc->AddTag("TYPE", &aInt); // 0
  widgtxtc->AddTag("OFFSET", &aLong);
  widgtxtc->AddTag("CH", &aByte);
  // insert into structList
  structList.push_back( widgtxtc);

  DStructDesc* widgtxtst = new DStructDesc( "WIDGET_TEXT_STR");
  widgtxtst->AddTag("ID", &aLong);
  widgtxtst->AddTag("TOP", &aLong);
  widgtxtst->AddTag("HANDLER", &aLong);
  widgtxtst->AddTag("TYPE", &aInt); // 1
  widgtxtst->AddTag("OFFSET", &aLong);
  widgtxtst->AddTag("STR", &aString);
  // insert into structList
  structList.push_back( widgtxtst);

  DStructDesc* widgtxts = new DStructDesc( "WIDGET_TEXT_SEL");
  widgtxts->AddTag("ID", &aLong);
  widgtxts->AddTag("TOP", &aLong);
  widgtxts->AddTag("HANDLER", &aLong);
  widgtxts->AddTag("TYPE", &aInt); // 3
  widgtxts->AddTag("OFFSET", &aLong);
  widgtxts->AddTag("LENGTH", &aLong);
  // insert into structList
  structList.push_back( widgtxts);
  
  DStructDesc* widgtxtd = new DStructDesc( "WIDGET_TEXT_DEL");
  widgtxtd->AddTag("ID", &aLong);
  widgtxtd->AddTag("TOP", &aLong);
  widgtxtd->AddTag("HANDLER", &aLong);
  widgtxtd->AddTag("TYPE", &aInt); // 2
  widgtxtd->AddTag("OFFSET", &aLong);
  widgtxtd->AddTag("LENGTH", &aLong);
  // insert into structList
  structList.push_back( widgtxtd);

  DStructDesc* widgver = new DStructDesc( "WIDGET_VERSION");
  widgver->AddTag("STYLE", &aString);
  widgver->AddTag("TOOLKIT", &aString);
  widgver->AddTag("RELEASE", &aString);
  // insert into structList
  structList.push_back( widgver);
}

void InitObjects()
{

  sigControlC = false;
  debugMode   = 0;

  fileUnits.resize( maxLun); // 0-127 -> 1-128 within GDL for files

  // initialize GDL system variables
  SysVar::InitSysVar();

  // initialize struct descriptors which are not system variables
  InitStructs();
  // add internal memeber subroutines
  SetupOverloadSubroutines();
  
  // graphic devices must be initialized after system variables
  // !D must already exist
  GraphicsDevice::Init();

  // preferences
  //  Preferences::Init();

#ifdef HAVE_LIBWXWIDGETS

  // some X error message suggested this call
  XInitThreads();

  // initialize widget system
  GDLWidget::Init();
#endif
}

// returns GDL lun, 0 on failure
DLong GetLUN()
{
  for( DLong lun=maxUserLun+1; lun <= fileUnits.size(); lun++)
    if( !fileUnits[ lun-1].InUse() && !fileUnits[ lun-1].GetGetLunLock())
    {
      fileUnits[ lun-1].SetGetLunLock( true);
      return lun;
    }
  
  return 0;
}

// for semantic predicate
bool IsFun(antlr::RefToken rT1)
{
  antlr::Token& T1=*rT1;

  // search for T1.getText() in function table and path
  string searchName=StrUpCase(T1.getText());

  //  cout << "IsFun: Searching for: " << searchName << endl;

  unsigned fLSize=funList.size();
  for( unsigned f=0; f<fLSize; f++)
    {
      if( funList[f]->Name() == searchName) return true;
    }

  //  cout << "Not found: " << searchName << endl;

  return false;
}

int ProIx(const string& n)
{
SizeT nF=proList.size();
for( SizeT i=0; i<nF; i++) if( Is_eq<DPro>(n)(proList[i])) 
  return (int)i;
return -1;
}

int FunIx(const string& n)
{
SizeT nF=funList.size();
for( SizeT i=0; i<nF; i++) if( Is_eq<DFun>(n)(funList[i]))
  return (int)i;
return -1;
}

int LibProIx(const string& n)
{
  SizeT nF=libProList.size();
  for( SizeT i=0; i<nF; i++) 
    {
      if( Is_eq<DLibPro>(n)(libProList[i])) return (int)i;
    }
  return -1;
}

int LibFunIx(const string& n)
{
  SizeT nF=libFunList.size();
  
  for( SizeT i=0; i<nF; i++) 
    {
      if( Is_eq<DLibFun>(n)(libFunList[i])) return (int)i;
    }
  return -1;
}

// returns the endian of the current machine
bool BigEndian()
{
  // a long should at least have two bytes
  // big endian -> msb first (msb is 0 here)
  static const unsigned long int s = 0x0001;
  static const bool bigEndian = !(*reinterpret_cast<const unsigned char*>( &s));
  return bigEndian;
}

// test---------------

void breakpoint()
{
  static SizeT num=1;
  cout << "objects.cpp: at breakpoint(): " << num << endl;
  num++;
}


#ifndef _OPENMP
int get_suggested_omp_num_threads() {
  return 1;
}
#endif

#if defined _OPENMP
int get_suggested_omp_num_threads() {

  int default_num_threads=1, suggested_num_threads=1;
  
  char* env_var_c;
  env_var_c = getenv ("OMP_NUM_THREADS");
  if(env_var_c) 
    {
      return atoi(env_var_c);
    }
  //    cout<<"OMP_NUM_THREADS is not defined"<<endl;
  
  //set number of threads for appropriate OS
  int avload = 0;
  int nbofproc = omp_get_num_procs();
  FILE *iff;
    
#if defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
  //  cout<<"is MAC/*BSD"<<endl;
  iff= popen("echo $(sysctl -n vm.loadavg|cut -d\" \" -f 3)", "r");
  if (!iff)
    {
      return default_num_threads;
    }
      
#elif defined(__linux__) || defined(__gnu_linux__) || defined(linux)
  //cout<<"is linux"<<endl;
  iff= popen("cat /proc/loadavg |cut -d\" \" -f3", "r");
  if (!iff)
    {
      return default_num_threads;
    }
   
#elif defined (__unix) || defined(__unix__)
  iff=freopen("/proc/loadavg","r",stderr);
  fclose(stderr);
  if(!iff)
    {
      cout<<"your OS is not supported"<<endl;
      return default_num_threads;
    }
  iff= popen("cat /proc/loadavg 2>/dev/null|cut -d\" \" -f3", "r");
  if (!iff)
    {
      return default_num_threads;
    }

//#elif defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
#elif defined(_MSC_VER)
  cout<<"get_suggested_omp_num_threads(): is windows"<<endl;
  iff= _popen("wmic cpu get loadpercentage|more +1", "r");
  if (!iff)
    {
      return default_num_threads;
    }
  char buffer[4];
  char* c;
  c=fgets(buffer, sizeof(buffer), iff);
  _pclose(iff);
  if(!c)
    {
      return default_num_threads;
    }
  int count=0;
  while(count < sizeof(buffer) && buffer[count]!='\0' && buffer[count]!=' ')count++;
  for(int i=1,j=1;i<=count;i++,j*=10)
  {
    if( buffer[count-i] != ' ' && buffer[count-i] != '\t')
      avload+=(buffer[count-i]-'0')*j;
  }
  suggested_num_threads=nbofproc-(int)(avload*((float)nbofproc/100)+0.5);
  return suggested_num_threads;

#else 
  cout<<"Can't define your OS"<<endl;
  return default_num_threads;
#endif

  //  cout << "Nb Procs.: " << nbofproc <<  endl;
  // cout << "nb Thead computed: " << nbofproc-(int)(avload+0.5) << endl;

  // if the following is commented out, there is no return statement
  // this lead to FILE_INFO in TEST_FILE_COPY fail
#ifndef _MSC_VER
  
  char buffer[4];
  char* c;
  c=fgets(buffer, sizeof(buffer), iff);
  pclose(iff);
  if(!c)
    {
      return default_num_threads;
    }
  //   cout<<buffer[0]<<" "<<buffer[1]<<endl;
  avload=(buffer[0]-'0')+((buffer[2]-'0')>5?1:0);

  suggested_num_threads=nbofproc-avload;
#endif  
  return suggested_num_threads;
}
#endif


