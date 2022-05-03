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
* It evaluates the difference between consecutive values for filtering as well.
* The library caches the recent input value as well as consecutive value change, so that all methods can be used on it without any argument, which avoids using always the same input value.
* If none input value has been provided since creation of the instance object at calling some method without input argument, the zero value is implicitly used as a cached value.
* Until an input value is provided and cached, the instance object is considered as not initialized. In that case all methods returning the logical value returns `false`.
* At the very first input value since creation of the instance object, the values change from previous value is considered as zero.


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
* **test_filter_change_float.cpp**: Test file providing test cases for change management of float values filtering.


<a id="constants"></a>

## Constants
* **VERSION**: Name and semantic version of the library.


<a id="interface"></a>

## Interface
* [gbj_appfilter()](#gbj_appfilter)
* [limit()](#limit)
* [init()](#init)

### Setters
* [setMinimum()](#setRange)
* [setMaximum()](#setRange)
* [setDifference()](#setDifference)
* [setValue()](#setValue)

### Getters
* [getMinimum()](#getRange)
* [getMaximum()](#getRange)
* [getDifference()](#getDifference)
* [getValue()](#getValue)
* [getChange()](#getChange)
* [isInit()](#isInit)
* [isValid()](#isValid)
* [isInvalid()](#isValid)
* [isJump()](#isJump)
* [isLow()](#isOutside)
* [isHigh()](#isOutside)
* [isDecr()](#polarity)
* [isIncr()](#polarity)
* [isEqual()](#polarity)


<a id="gbj_appfilter"></a>

## gbj_appfilter()

#### Description
Constructor creates the class instance with initial valid range limits and maximal valid change of consecutive inputs applied at filtering.
* It is templated for various data types.
* If constructor has just one argument, that one is considered as the maximum of general valid range.
* If both arguments for valid range are defined, the constructor sorts them internally if needed.
* Initial limits and difference can be overriden by corresponding setters.

#### Syntax
    gbj_appfilter<typename DAT>(DAT valMax, DAT valMin, DAT difMax)

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


* **difMax**: Maximal consecutive change of values for their validity. Only the absolute value of the difference is internally stored. It is limited to the current valid range, i.e., to the difference between maximum and minimum of valid range.
  * *Valid values*: by templated data type
  * *Default value*: 0

#### Returns
Object performing filtering management.

#### Example
```cpp
#include "gbj_appfilter.h"

gbj_appfilter filterFloat = gbj_appfilter(54.3, 23.4, 10.5);
gbj_appfilter<int> filterInt = gbj_appfilter<int>(50, -10);
gbj_appfilter<unsigned int> filterUint = gbj_appfilter<unsigned int>(50);
```

#### See also
[setMinimum(), setMaximum()](#setRange)

[setDifference()](#setDifference)

[Back to interface](#interface)


<a id="init"></a>

## init()

#### Description
The method initializes the instance object and sets its status as it would be just created, i.e., without any input value cached.
* It might be useful for unit tests.
* It is used for resetting the change filtering management.

#### Syntax
    void init()

#### Parameters
None

#### Returns
None

#### See also
[gbj_appfilter()](#gbj_appfilter)

[isInit()](#isInit)

[Back to interface](#interface)


<a id="limit"></a>

## limit()

#### Description
The overloaded method constrains either the input value or cached value to actual valid range defined either by [constructor](#gbj_appfilter) or by [setters](#setRange).
* In case of no input argument, the method uses the internally cached value input by some of previous methods calls.
* Implicit (initial, default) cached value is zero.
* If input or cached value is less than current minimum of valid range, it returns that minimum.
* If input or cached is greater than current maximum of valid range, it returns that maximum.

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


<a id="setDifference"></a>

## setDifference()

#### Description
The method sets the maximal valid difference between consecutive input values.
* Input value in contrast to the constructor is not sanitized neither sorted internally, just stored in the instance object.
* Only the absolute value is internally stored.
* The valid difference is limited to the current valid range, i.e., to the difference between maximum and minimum of valid range.

#### Syntax
    void setDifference(DAT data)

#### Parameters
* **data**: Corresponding maximal valid difference.
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
The method caches provided input value for further usage by methods without input argument as well as initiates for change filtering management.

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

[isInit()](#isInit)

[Back to interface](#interface)


<a id="getRange"></a>

## getMinimum(), getMaximum()

#### Description
The particular method returns current (recently set) extreme value for the valid range.

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


<a id="getDifference"></a>

## getDifference()

#### Description
The method returns current (recently set) maximal valid difference of consecutive values.

#### Syntax
    DAT getDifference()

#### Parameters
None

#### Returns
Recent valid difference.

#### See also
[setDifference()](#setDifference)

[Back to interface](#interface)


<a id="getValue"></a>

## getValue()

#### Description
The method returns currently cached value, which is recently input value, but not filtered against current valid range.

#### Syntax
    DAT getValue()

#### Parameters
None

#### Returns
Recently cached value.

#### See also
[setValue()](#setValue)

[Back to interface](#interface)


<a id="isInit"></a>

## isInit()

#### Description
The method returns flag determining whether the library instance object is initiated, i.e., whether some input value has been cached.

#### Syntax
    bool isInit()

#### Parameters
None

#### Returns
Flag determining initiation status of the instance object.

#### See also
[init()](#init)

[Back to interface](#interface)


<a id="isValid"></a>

## isValid(), isInvalid()

#### Description
The particular overloaded method returns flag determining corresponding result of checking the input or recently cached value against the valid range and against valid consecutive change, if the maximal valid difference has been defined.

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
Flag determining result of checking the input or recently cached value against the valid range and maximal valid difference.

[Back to interface](#interface)


<a id="isJump"></a>

## isJump()

#### Description
The overloaded method returns flag determining whether the consecutive current or recently cached value change exceeds the maximal valid difference, if it has been defined.
* It is the main method for consecutive change filtering management.
* If the change is above the valid difference, the value is invalid as well.
* The method always returns false flag, if the maximal valid difference has not been initialized yet.
* The method always returns false flag, if the instance object has not been initialized yet, i.e., no input value has been used including this call since the instance object creation or initiation.

#### Syntax
    bool isJump(DAT data)
    bool isJump()

#### Parameters
* **data**: Value to be checked against the current maximal valid difference.
  * *Valid values*: by templated data type
  * *Default value*: none

#### Returns
Flag determining result of checking consecutive change of the input or recently cached value against the maximal valid difference.

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


<a id="polarity"></a>

## isDecr(), isIncr(), isEqual()

#### Description
The particular overloaded method returns flag determining whether the cached consecutive value change is negative (decremented), positive (incremented), or none (equal).
* The methods always return false flag, if the instance object has not been initialized yet, i.e., no input value has been used used including this call since the instance object creation or initiation.
* The methods are usable regardless of definition of maximal valid difference.

#### Syntax
    bool isDecr(DAT data)
    bool isDecr()
    bool isIncr(DAT data)
    bool isIncr()
    bool isEqual(DAT data)
    bool isEqual()

#### Parameters
* **data**: Value to be checked against the polarity of the consecutive value change.
  * *Valid values*: by templated data type
  * *Default value*: none

#### Returns
Flag determining result of checking the consecutive value change polarity.

[Back to interface](#interface)
