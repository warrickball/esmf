// $Id: ESMCI_WebServNetEsmfClient.h,v 1.2 2010/11/02 18:36:04 ksaint Exp $
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

#ifndef ESMCI_WebServNetEsmfClient_H
#define ESMCI_WebServNetEsmfClient_H

#include <stdlib.h>
#include <string>
#include <vector>

#include "ESMCI_WebServServerSocket.h"
#include "ESMCI_WebServClientSocket.h"
#include "ESMCI_WebServNetEsmf.h"

using namespace std;

//-------------------------------------------------------------------------
//BOPI
// !CLASS: ESMCI::ESMCI_WebServNetEsmfClient
//
// !DESCRIPTION:
//
// The code in this file defines the C++ NetEsmfClient members and method
// signatures (prototypes).  The companion file ESMCI\_WebServNetEsmfClient.C
// contains the full code (bodies) for the NetEsmfClient methods.
//
// This class provides the capability to connect and communicate with a
// ESMF Component (Grid or Coupler) service.  
//
//EOPI
//-------------------------------------------------------------------------

namespace ESMCI
{

  class ESMCI_WebServNetEsmfClient 
  {
  public:

	  // constructor and destructor
	  ESMCI_WebServNetEsmfClient(const char*  host,
                                int          port);
	  ~ESMCI_WebServNetEsmfClient();

     // methods to setup the connection parameters
	  void setHost(const char*  host);
	  void setPort(int  port);

     // methods to send client requests to the server
     int  newClient(const char*  clientName);
     int  init(int  clientId);
     int  init(int  clientId, const char*  filename);
     int  run(int  clientId);
     int  final(int  clientId);
     int  state(int  clientId);
     vector<string>  files(int  clientId);
	  string  getData(int      clientId, 
                     string   varName, 
                     string   time, 
                     string   lat, 
                     string   lon, 
                     string&  dataValue);
     int  end(int  clientId);
   
     // low-level communications methods
	  int  sendRequest(int    request,
                      int    length = 0,
                      void*  data = NULL);

	  int  getResponse(int    request,
                      int&   length,
                      void*  data);

	  int  connect();
	  void disconnect();

  private:

     // methods to handle request ids
	  int   getRequestId(const char  request[]);
	  char* getRequestFromId(int  id);

	  char*			theHost;			// the name of the machine that hosts the svc
	  int				thePort;			// the port number for the service
	  char			theMsg[8192];	// the message buffer

	  ESMCI_WebServClientSocket	
						theSocket;		// the socket connection to the service
  };

}  // end namespace


#endif 	// ESMCI_WebServNetEsmfClient_H
