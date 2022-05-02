<a id="library"></a>

# gbj\_appfilter
This is an application library, which is used usually as a project library for particular PlatformIO project. It unifies and encapsulates the functionality of `data filtering` with valid data range for measures with various data types. The encapsulation provides following advantages:

* Functionality is hidden from the main sketch.
* The library follows the principle `separation of concerns`.
* Update in library is valid for all involved projects.
* The library manages the filtering and provides the same interface for various data types without need of comparison expressions.


## Fundamental functionality
* The library is templated, so that it can utilize various data types.
* It provides filtering of samples against their valid range by setting minimal and maximal valid values.
* The library caches the recent input value, so that all methods can be used on it without any argument, which avoids using always the same input value.
* If none input value has been provided since creation of the instance object at calling some method without input argument, the zero value is implicitly used as a cached value.


<a id="dependency"></a>

## Dependency
#### Arduino platform
* **Arduino.h**: Main include file for the Arduino SDK.
* **inttypes.h**: Integer type conversions. This header file includes the exact-width integer definitions and extends them with additional facilities provided by the implementation.

#### Espressif ESP8266 platform
* **Arduino.h**: Main include file for the Arduino platform.

#### Espressif ESP32 platform
* **Arduino.h**: Main include file for the Arduino platform.

#### Particle platform
* **Particle.h**: Includes alternative (C++) data type definitions.


<a id="tests"></a>

## Unit testing
The subfolder `tests` in the folder `extras`, i.e., `gbj_appfilter/extras/test`, contains testing file(s) with unit tests of library [gbj_appfilter](#library) executable by [Unity](http://www.throwtheswitch.org/unity) test runner. Each testing file should be placed in an individual test folder of a particular project, usually in the structure `test/<testname>/<testfile>`.
* **test_filter.cpp**: Test file providing test cases for standard filtering.


<a id="constants"></a>

## Constants
* **VERSION**: Name and semantic version of the library.


<a id="interface"></a>

## Interface
* [gbj_appfilter()](#gbj_appfilter)
* [limit()](#limit)

### Setters
* [setMinimum()](#setRange)
* [setMaximum()](#setRange)
* [setValue()](#setValue)

### Getters
* [getMinimum()](#getRange)
* [getMaximum()](#getRange)
* [getValue()](#getValue)
* [isValid()](#isValid)
* [isInvalid()](#isValid)
* [isLow()](#isOutside)
* [isHigh()](#isOutside)


<a id="gbj_appfilter"></a>

## gbj_appfilter()

#### Description
Constructor creates the class instance with initial valid range limits applied at filtering.
* It is templated for various data types.
* If constructor has just one argument, that one is considered as the maximum of general valid range.
* If both arguments are defined, the constructor sorts them internally if needed.
* Initial limits can be overriden by corresponding [setters](#setRange).

#### Syntax
    gbj_appfilter<typename DAT>(DAT valMax, DAT valMin)

#### Parameters
* **DAT**: Data type of input values.
  * *Valid values*: various
  * *Default value*: float


* **valMax**: Maximum of valid range.
  * *Valid values*: by templated data type
  * *Default value*: none


* **valMin**: Minimum of valid range.
  * *Valid values*: by templated data type
  * *Default value*: 0

#### Returns
Object performing filtering management.

#### Example
```cpp
#include "gbj_appfilter.h"

gbj_appfilter filterFloat = gbj_appfilter(54.3, 23.4);
gbj_appfilter<int> filterInt = gbj_appfilter<int>(50, -10);
```

[Back to interface](#interface)


<a id="limit"></a>

## limit()

#### Description
The overloaded method constrains either the input value or cached value to actual valid range defined either by [constructor](#gbj_appfilter) or by [setters](#setRange).
* In case of no input argument, the method uses the internally cached value input by some previous method, but not only by this one.
* Implicit (initial, default) cached value is zero.
* If input or cached value is less than current minimum of valid range, it returns that minimum.
* If input or cached is greater than current maximum of valid range, it returns that maximum.
* The method internally caches the input value for subsequent usage by getters.

#### Syntax
    DAT limit(DAT data)
    DAT limit()

#### Parameters
* **data**: Value to be constrained.
  * *Valid values*: by templated data type
  * *Default value*: none

#### Returns
Value limited to the current valid range.

#### See also
[gbj_appfilter()](#gbj_appfilter)

[setMinimum(), setMaximum()](#setRange)

[Back to interface](#interface)


<a id="setRange"></a>

## setMinimum(), setMaximum()

#### Description
The particular method sets the corresponding extreme of the valid range for filtering.
* Input value in contrast to the constructor is not sanitized neither sorted internally, just stored in the instance object.

#### Syntax
    void setMinimum(DAT data)
    void setMaximum(DAT data)

#### Parameters
* **data**: Corresponding extreme value of the valid range.
  * *Valid values*: by templated data type
  * *Default value*: none

#### Returns
None

#### See also
[gbj_appfilter()](#gbj_appfilter)

[Back to interface](#interface)


<a id="setValue"></a>

## setValue()

#### Description
The method caches provided input value for further usage by methods without input argument.

#### Syntax
    void setValue(DAT data)

#### Parameters
* **data**: Value to be cached for filtering.
  * *Valid values*: by templated data type and valid range
  * *Default value*: none

#### Returns
None

#### See also
[getValue()](#getValue)

[Back to interface](#interface)


<a id="getRange"></a>

## getMinimum(), getMaximum()

#### Description
The particular method returns recently set extreme value for the valid range.

#### Syntax
    DAT getMinimum()
    DAT getMaximum()

#### Parameters
None

#### Returns
Corresponding recent extreme value of the valid range.

#### See also
[setMinimum(), setMaximum()](#setRange)

[Back to interface](#interface)


<a id="getValue"></a>

## getValue()

#### Description
The method returns currently cached value, which recently input value, but not filtered against current valid range.

#### Syntax
    DAT getValue()

#### Parameters
None

#### Returns
Recently cached value.

#### See also
[setValue()](#setValue)

[Back to interface](#interface)


<a id="isValid"></a>

## isValid(), isInvalid()

#### Description
The particular overloaded method returns flag determining corresponding result of checking the input or recently cached value against the valid range.

#### Syntax
    bool isValid(DAT data)
    bool isValid()
    bool isInvalid(DAT data)
    bool isInvalid()

#### Parameters
* **data**: Value to be checked against the current valid range.
  * *Valid values*: by templated data type
  * *Default value*: none

#### Returns
Flag determining result of checking the input or recently cached value against the valid range.

[Back to interface](#interface)


<a id="isOutside"></a>

## isLow(), isHigh()

#### Description
The particular overloaded method returns flag determining whether the input or recently cached value is below or above the valid range.
* If the value is outside the valid range, it is invalid as well.

#### Syntax
    bool isLow(DAT data)
    bool isLow()
    bool isHigh(DAT data)
    bool isHigh()

#### Parameters
* **data**: Value to be checked against an extreme of the current valid range.
  * *Valid values*: by templated data type
  * *Default value*: none

#### Returns
Flag determining result of checking the input or recently cached value against corresponding extreme of the valid range.

[Back to interface](#interface)
