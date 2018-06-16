# Changelog

## [v0.3.1] - 16.06.2018

**[+]** added `selector` - tool for compile-time branching; `#include <ex/meta/selector>`  
**[+]** added `math_type` - compile-time type classification; `#include <ex/meta/math_type>`  
**[+]** added word splitting and combining tool; `#include <ex/encoding/word>`   

**[*]** configurable notice policy `ex::policy::DefaultNotice`; `#include <ex/common/policy>`  
**[*]** `Expected<T>` -> `expected<T>` + function renaming; `#include <ex/expected>`    
**[*]** eliminated extra namespace: `meta`;  
**[*]** all `meta` tools now in lowercase;  
**[*]** added `NoNotice` policy; `#include <ex/policy/notice>`  
**[*]** rename `type_assert` to `concept`(similar to new language feature p1079r0); `#include <ex/meta/concept>`  
**[*]** interface of `expected<T>` updated; `#include <ex/expected>`  

**[-]** removed `range_check_assert`; `#include <ex/range_check>`


## [v0.3.0] - 27.04.2018

**[+]** compile-time branching: **bool_selector**; `#include <ex/meta/selector>`  
**[+]** compile-time type constrains: TYPE_ASSERT, TYPE_ASSERT_SAME; `#include <ex/meta/type_assert>`    
**[+]** added **googletest** framework as submodule;  
**[+]** unit tests for **ct** module; `ex/test/ct`  
**[+]** use `index_t` for indexing (`int32_t` for now); `#include <ex/common/type>`
  
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



