# Changelog

## [v0.3.0] - 24.04.2018

**[+]** type for compile-time branching: **BoolSelector**; `#include <ex/meta/selector>`  
**[+]** compile-time type constrains: TYPE_ASSERT, TYPE_ASSERT_SAME; `#include <ex/meta/type_assert>`  
**[+]** added **googletest** framework as submodule;  
**[+]** unit tests for **ct** module; `ex/test/ct`  


**[*]** split meta into: **pack**, **sequence**; `#include <ex/meta/...>`  
**[*]** move lib **{fmt}** to submodule;

## [v0.2.0] - 23.02.2017

**[*]** move on C++14;

**[+]** Compile-time functions [**ct** namespace]:
* **string**: meta_str, strcat, set_char, substr, strfill, ...;
* **math**: sqrt, min/max, abs, factorial;  

**[+]** class **Logger**; `#include <ex/log/logger>`  
**[+]** Alecsandrescu's **Expected**; `#include <ex/expected>`  
**[+]** Alecsandrescu's **ScopeGuard**; `#include <ex/scopeguard>`  
**[+]** meta-template programming tools - **[meta]**; `#include <ex/meta>`   
**[+]** intagrated **{fmt}** library;  `#include <ex/format>`  
**[+]** variables ranges validation - **[range_check]**; `#include <ex/range_check>`   
**[+]** assertation; `#include <ex/assert>`   
**[+]** object pool with polices; `#include <ex/pool>`  
**[+]** life-cycle (creation/destroy/move/...) tracing: **LiveTrace**; `#include <ex/placebo>`  
  
**[-]** module **[debug]**;
  
## [v0.1.3] - 05.04.2016

**[+]** module **[platform]**;  
**[+]** documentation;


## [v0.1.2] - 31.03.2015

First release



