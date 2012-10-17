//   Copyright 2012 - Global Vision Systems
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

/*
 * ServiceUtils.h
 *
 *  Created on: 10 mai 2012
 *      Author: simon
 */
#ifndef SERVICEUTILS_H_
#define SERVICEUTILS_H_
#include <usServiceInterface.h>
#define DECLARE_SERVICE_INTERFACE(ServiceType) \
    US_DECLARE_SERVICE_INTERFACE(ServiceType, #ServiceType)


/**
  * Macros for import/export declarations
  */
#if defined(WIN32)
  #define DS_ABI_EXPORT __declspec(dllexport)
  #define DS_ABI_IMPORT __declspec(dllimport)
  #define DS_ABI_LOCAL
#else
  #if __GNUC__ >= 4
    #define DS_ABI_EXPORT __attribute__ ((visibility ("default")))
    #define DS_ABI_IMPORT __attribute__ ((visibility ("default")))
    #define DS_ABI_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DS_ABI_EXPORT
    #define DS_ABI_IMPORT
    #define DS_ABI_LOCAL
  #endif
#endif


#endif /* SERVICEUTILS_H_ */

