// $Id: ESMCI_WebServSocketUtils.h,v 1.2 2010/11/02 18:36:04 ksaint Exp $
//
// Earth System Modeling Framework
// Copyright 2002-2010, University Corporation for Atmospheric Research,
// Massachusetts Institute of Technology, Geophysical Fluid Dynamics
// Laboratory, University of Michigan, National Centers for Environmental
// Prediction, Los Alamos National Laboratory, Argonne National Laboratory,
// NASA Goddard Space Flight Center.
// Licensed under the University of Illinois-NCSA License.
//
//-------------------------------------------------------------------------
// (all lines below between the !BOP and !EOP markers will be included in
//  the automated document processing.)
//-------------------------------------------------------------------------
// these lines prevent this file from being read more than once if it
// ends up being included multiple times


#ifndef ESMCI_WebServSocketUtils_H
#define ESMCI_WebServSocketUtils_H

//-------------------------------------------------------------------------
//BOPI
//
// !DESCRIPTION:
//
// The code in this file defines the C++ SocketUtils function 
// signatures (prototypes).  The companion file ESMCI\_WebServSocketUtils.C
// contains the full code (bodies) for the SocketUtils functions.
//
// This file contains some utility functions that don't belong in a class,
// but are needed to create and use the server and client sockets.
//
//EOPI
//-------------------------------------------------------------------------


namespace ESMCI
{

  //***
  // Default wait time before timing out
  //***
  #define TWAIT	(10)

  // Levels of severity for "notify" messages
  // (KDS: I think this is going to be replaces by ESMF error hand.ing codes
  enum Severity
  {
	  PRINT,
	  WARN,
	  ERROR,
	  FATAL
  };

  // Function that prints error messages to stderr
  // (KDS: I think this is going to be replaces by ESMF error hand.ing codes
  void  ESMCI_WebServNotify(const char  msg[],
                            Severity    severity,
                            const char  proc[]);

  // Functions to send and receive data using sockets
  int  ESMCI_WebServSend(int    fd,
                         int    size,
                         void*  data);

  int  ESMCI_WebServRecv(int    fd,
                         int    size,
                         void*  data);

  int  ESMCI_WebServRecv(int          fd,
                         const char*  s);


} // end namespace

#endif 	// ESMCI_WebServSocketUtils_H
