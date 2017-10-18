// $Id$
//
// Earth System Modeling Framework
// Copyright 2002-2017, University Corporation for Atmospheric Research, 
// Massachusetts Institute of Technology, Geophysical Fluid Dynamics 
// Laboratory, University of Michigan, National Centers for Environmental 
// Prediction, Los Alamos National Laboratory, Argonne National Laboratory, 
// NASA Goddard Space Flight Center.
// Licensed under the University of Illinois-NCSA License.
//
//-------------------------------------------------------------------------
// (all lines below between the !BOP and !EOP markers will be included in 
//  the automated document processing.)
//-----------------------------------------------------------------------------
// these lines prevent this file from being read more than once if it
// ends up being included multiple times

#ifndef ESMCI_RHandle_H
#define ESMCI_RHandle_H

//-----------------------------------------------------------------------------
//BOPI
// !CLASS:  ESMCI::RouteHandle - Handle which points to precomputed information
//              
//
// !DESCRIPTION:
//
// The code in this file defines the C++ {\tt RouteHandle} class and declares
// method signatures (prototypes).  The companion file {\tt ESMCI_RHandle.C}
// contains the full code (bodies) for the {\tt RouteHandle} methods.
//
//EOPI
//-------------------------------------------------------------------------

namespace ESMCI {
  class RouteHandle;
}

#include "ESMCI_Base.h"       // Base is superclass to RouteHandle
#include "ESMCI_Array.h"

//-------------------------------------------------------------------------

namespace ESMCI {

  // classes and structs

  typedef enum { 
    ESMC_UNINITIALIZEDHANDLE=1,
    ESMC_ARRAYXXE,
    ESMC_ARRAYBUNDLEXXE
  }RouteHandleType;

  // class definition
  class RouteHandle : public ESMC_Base {    // inherits from ESMC_Base class
    
#define RHSTORAGECOUNT  10

   private:
    RouteHandleType htype;          // type info
    void *storage[RHSTORAGECOUNT];  // storage used by specific communication
    //TODO: longer term do not store srcArray and dstArray, but just
    //TODO: some form of finger print that persists without relying on
    //TODO: Arrays to persist
    Array *srcArray;
    Array *dstArray;
 
   public:
    RouteHandle():ESMC_Base(-1){    // use Base constructor w/o BaseID increment
      // initialize the name for this RouteHandle object in the Base class
      ESMC_BaseSetName(NULL, "RouteHandle");
    }
    ~RouteHandle(){destruct();}
    static RouteHandle *create(int *rc);
    static RouteHandle *create(RouteHandle *rh, int *rc);
    static int destroy(RouteHandle *routehandle, bool noGarbage=false);
    int construct(void);
    int destruct(void);    
    RouteHandleType getType(void) const { return htype; }
    int setType(RouteHandleType h){ htype = h; return ESMF_SUCCESS; }
    void *getStorage(int i=0) const{
      if (i<0 || i>=RHSTORAGECOUNT)
        return NULL;
      return storage[i];
    }
    int setStorage(void *ptr, int i=0){
      if (i<0 || i>=RHSTORAGECOUNT)
        return ESMC_RC_ARG_BAD;
      storage[i] = ptr; 
      return ESMF_SUCCESS;
    }
    
    // fingerprinting of src/dst Arrays
    int fingerprint(Array *srcArrayArg, Array *dstArrayArg){
      srcArray = srcArrayArg;
      dstArray = dstArrayArg;
      return ESMF_SUCCESS;
    }
        
    // required methods inherited and overridden from the ESMC_Base class
    int validate() const;
    int print() const;

    // optimize for the communication pattern stored inside the RouteHandle
    int optimize() const;
    bool isCompatible(Array *srcArrayArg, Array *dstArrayArg, int *rc=NULL)
      const;
  };   // class RouteHandle

} // namespace ESMCI

#endif  // ESMCI_RHandle_H
