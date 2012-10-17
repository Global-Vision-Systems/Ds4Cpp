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
 * ModuleUtils.h
 *
 *  Created on: 14 juin 2012
 *      Author: simon
 */

#ifndef MODULEUTILS_H_
#define MODULEUTILS_H_

#define STRINGIZE_NX(A) #A

#if defined(_DEBUG)
#define MODULE_NAME(ModuleName) ModuleName##d
#define MODULE_NAME_CSTR(ModuleName) STRINGIZE_NX(MODULE_NAME(ModuleName))
#else
#define MODULE_NAME(ModuleName) ModuleName
#define MODULE_NAME_CSTR(ModuleName) #ModuleName
#endif

#endif /* MODULEUTILS_H_ */
