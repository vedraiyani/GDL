/* *************************************************************************
                          gdlwinstream.cpp  -  graphic stream M$ windows
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

#include "includefirst.hpp"

#include <iostream>

#include "gdlwinstream.hpp"

using namespace std;

void GDLWINStream::Init()
{
  plstream::init();

//   //  set_stream(); // private
//   plgpls( &pls);
//   XwDev *dev = (XwDev *) pls->dev;
//   XwDisplay *xwd = (XwDisplay *) dev->xwd;

//   wm_protocols = XInternAtom( xwd->display, "WM_PROTOCOLS", false);  
//   wm_delete_window = XInternAtom( xwd->display, "WM_DELETE_WINDOW", false);
  
//   XSetWMProtocols( xwd->display, dev->window, &wm_delete_window, 1);
//   XFlush( xwd->display);
}

void GDLWINStream::EventHandler()
{
//   if( !valid) return;

//   XwDev *dev = (XwDev *) pls->dev;
//   XwDisplay *xwd = (XwDisplay *) dev->xwd;
  
//   XEvent event;
//   if( XCheckTypedWindowEvent( xwd->display, dev->window, 
// 			      ClientMessage, &event))
//     {
//       if( event.xclient.message_type == wm_protocols &&
// 	  event.xclient.data.l[0] == wm_delete_window)  
// 	{
// 	  valid = false;
// 	  return; // no more event handling
// 	}
//       else
// 	XPutBackEvent( xwd->display, &event);
//     }

//   // plplot event handler
//   plstream::cmd( PLESC_EH, NULL);
}

