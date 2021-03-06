/* *************************************************************************
                          graphicsdevice.hpp  -  GDL graphical output
renamed from: graphics.hpp                          
                             -------------------
    begin                : July 22 2002
    copyright            : (C) 2002 by Marc Schellens
    email                : m_schellens@users.sf.net
 ***************************************************************************/

/* *************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/* 

GDL Graphic subsytem:

GraphicsDevice - base subsystem class
DeviceXXX - dervived from Graphics, subsystem for device XXX


GDLGStream - base graphic stream class (= windows, printer page)
GDLXXXStream - derived from GDLGStream for XXX type of stream


So for each device XXX there is a:
DeviceXXX
and at least one
GDLXXXStream
 
Devices are (note that on a given platform not all devices are available): 
X   - X windows (GDLXStream, GDLWXStream)
WIN - Windows
PS  - postscript output
...

*/


#ifndef GRAPHICSDEVICE_HPP_
#define GRAPHICSDEVICE_HPP_

#include <vector>

#include "datatypes.hpp" // DByte
#include "dstructgdl.hpp"
#include "gdlgstream.hpp"

const UInt ctSize = 256;

class GDLCT
{
  DByte  r[ ctSize];
  DByte  g[ ctSize];
  DByte  b[ ctSize];

  UInt    actSize;

  std::string name;

public:
  GDLCT( const std::string& n, DByte* r_, DByte* g_, DByte* b_, SizeT nCol = ctSize):
    actSize( nCol), name( n)
  {
    SizeT i=0;
    for(;i<nCol;++i)
      {
	r[i] = r_[i];
	g[i] = g_[i];
	b[i] = b_[i];
      }
    for(;i<ctSize;++i)
      {
	r[i] = 0;
	g[i] = 0;
	b[i] = 0;
      }
  }

  // default is greyscale
  GDLCT(): actSize( ctSize), name("DEFAULT")
  {
    for( UInt i=0; i<ctSize; i++)
      {
	r[i]=g[i]=b[i]=i;
      }
  }

  ~GDLCT() {}

  bool Get( PLINT r_[], PLINT g_[], PLINT b_[], UInt nCol=ctSize) const;

  bool Get( UInt ix, DByte& r_, DByte& g_, DByte& b_) const;
  bool Set( UInt ix, DByte r_, DByte g_, DByte b_); // RGB
  bool SetHLS( UInt ix, DFloat h, DFloat l, DFloat s);
  bool SetHSV( UInt ix, DFloat h, DFloat s, DFloat v);

  std::string Name() const { return name;}
};


class   GraphicsDevice;
typedef std::vector< GraphicsDevice*> DeviceListT;

// class wxDC;
class GraphicsDevice
{
  static void InitCT();         // preset CT and actCT

  static GraphicsDevice*    actDevice;
  static DeviceListT  deviceList;
  static GraphicsDevice*    actGUIDevice;

  static void DefineDStructDesc(); // modifies structList

protected:
  static int wTag, xSTag, ySTag, xVSTag, yVSTag, n_colorsTag; // !D tag indices

  static std::vector<GDLCT> CT; // predefined colortables
  static GDLCT           actCT; // actual used colortable

  std::string         name;
  DStructGDL*         dStruct;

  void GetWinSize( DLong& x, DLong& y)
  {
    int tag = dStruct->Desc()->TagIndex( "X_SIZE");
    DLongGDL* xSize = static_cast<DLongGDL*>( dStruct->GetTag( tag));
    tag = dStruct->Desc()->TagIndex( "Y_SIZE");
    DLongGDL* ySize = static_cast<DLongGDL*>( dStruct->GetTag( tag));
    x = (*xSize)[0];
    y = (*ySize)[0];
  }

public:
  GraphicsDevice();
  virtual ~GraphicsDevice();

  static void Init();
  static void DestroyDevices();
  static void HandleEvents();

  static void LoadCT(UInt iCT);

  static GDLCT*      GetCT() { return &actCT;}
  static GDLCT*      GetCT( SizeT ix) { return &CT[ix];}
  static SizeT       N_CT() { return CT.size();}
  static bool        SetDevice( const std::string& devName);
  static GraphicsDevice*   GetDevice() { return actDevice;}
  static GraphicsDevice*   GetGUIDevice() { return actGUIDevice;}
  static DStructGDL* DStruct()   { return actDevice->dStruct;} 
  
  const DString     Name() { return name;}

  virtual GDLGStream* GetStreamAt( int wIx) const     { return NULL;}
  virtual GDLGStream* GetStream( bool open=true)      { return NULL;}
  virtual bool WSet( int ix)                          { return false;}
  virtual int  WAdd()                                 { return false;}

  // for WIDGET_DRAW
  virtual bool GUIOpen( int wIx, int xSize, int ySize) { return false;} 

  // for plot windows
  virtual bool WOpen( int ix, const std::string& title,
		      int xsize, int ysize, 
		      int xpos, int ypos)             { return false;}
  virtual bool WSize( int ix,
		      int* xsize, int* ysize, 
		      int* xpos, int* ypos)           { return false;}
  virtual bool WShow( int ix, bool show, bool iconic) { return false;}
  virtual bool WState( int ix)                        { return false;}
  virtual bool WDelete( int ix)                       { return false;}
  virtual int  MaxWin()                               { return 0;}
  virtual int  ActWin()                               { return -1;}
  virtual void EventHandler() {}

  virtual bool CloseFile()                            { return false;}
  virtual bool SetFileName( const std::string& f)     { return false;}
  virtual bool  Decomposed( bool value)               { return false;}
  virtual DLong GetDecomposed()                       { return -1;}
  virtual bool  SetGraphicsFunction( DLong value)     { return false;}
  virtual DLong GetGraphicsFunction()                 { return -1;}
  virtual bool CursorStandard( int value)             { return false;}
  virtual bool CursorCrosshair()                      { return false;}
  virtual bool UnsetFocus()                           { return false;}
  virtual bool EnableBackingStore(bool enable)        { return false;}
  virtual bool SetXPageSize( const float xs)          { return false;}
  virtual bool SetYPageSize( const float ys)          { return false;}
  virtual bool SetColor(const long color=0)           { return false;}
  virtual bool SetScale(const float)                  { return false;}
  virtual bool SetXOffset(const float)                { return false;}
  virtual bool SetYOffset(const float)                { return false;}
  virtual bool SetPortrait()                          { return false;}
  virtual bool SetLandscape()                         { return false;}
  virtual bool SetEncapsulated(bool)                  { return false;}

  // Z buffer device
  virtual bool ZBuffering( bool yes)                  { return false;}
  virtual bool SetResolution( DLong nx, DLong ny)     { return false;}

  // TVRD function for a device
  virtual BaseGDL* TVRD( EnvT* e) 
  {
    throw GDLException( "Device "+Name()+" does not support TVRD.");
  }
  
  virtual void TV( EnvT* e)
  {
    throw GDLException( "Device "+Name()+" does not support TV.");
  }

  virtual void ClearStream( DLong bColor)
  {
    throw GDLException( "Device "+Name()+" does not support ClearStream.");
  }
};

#endif

