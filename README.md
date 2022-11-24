SmartPointer
// TODO

## Table of Contents

- [Table of Contents](#table-of-contents)
- [About the Project](#about-the-project)
  - [SMART POINTERS](#smart-pointers)
  - [COPY SEMANTICS](#copy-semantics)
  - [MOVE SEMANTICS](#move-semantics)
  - [R-VALUE REFERENCE](#r-value-reference)
- [Project Status](#project-status)
- [Getting Started](#getting-started)
  - [Dependencies](#dependencies)
  - [Getting the Source](#getting-the-source)
  - [Installation](#installation)
  - [Usage](#usage)
- [Further Reading](#further-reading)
- [License](#license)
- [Authors](#authors)

## About the Project
### SMART POINTERS
Smart pointer class are a composition class that is designed to manage dynamically allocated memory, and ensure the memory gets deleted when the smart pointer goes out of scope.

- There are 4 types of smart pointers, auto_ptr, unique_ptr, shared_ptr and weak_ptr.
  - auto_ptr(NOT USE): introduced in c++98(no mechanisms for move semantics), deprecated in C++11 and removed in C++17. why was it removed? First, it implements "move semantics" thourgh the copy constructor and assigment operator,passing a std::auto_ptr by value to a function will cause your resource to get moved to the function parameter (and be destroyed at the end of the function when the function parameters go out of scope). Second, always deletes its contents using non-array delete. Third, it doesn’t play nice with a lot of the other classes in the standard library, including most of the containers and algorithms. This occurs because those standard library classes assume that when they copy an item, it actually makes a copy, not a move.
  - unique_ptr : It manage a single not-shareable resource. It disables copy semantics. std::make_unique(C++14) should be preferred to create a new unique_ptr.
  - shared_ptr : Used when you need multiple objects accessing the same resource. The resource is not destroyed(delete) until the last share_ptr managing is destroyed. share_ptr use copy semantics to create addiotional shared_ptr poiting to the same object. Use std::make_shared to create a new shared_ptr.
  - weak_ptr : Used when you need one or more object with the ability to view and access a resource managed by a share_ptr. weak_ptr is not considereded when determining whether the resource should be destroyed.

### COPY SEMANTICS
Allow our classes to be copied. This is done promarily via the copy constructor and the copy assignment operator.

### MOVE SEMANTICS
Class transfer ownership of the object rather than making a copy(Cheaper operation than copy). This is done primarily via the move contructor and move operator.

### EXPRESSIONS
An expression is a combination of literals, variables, operators and function calls than can be executed to produce a singula value. All expressions has two properties, a type and a value category. The type of the expression is equivalent to the type of the value, object, or function that results from the evaluated expression.

The type of an expression must be determined at compile time, however the value of an expression may be determined at either compiled time(if the expression is constexpr) or runtime (if the expression is not constexpr).

The value category of an expression indicates whether an expression resolves to a value, a function or an object of some kind.

### L VALUES AND R VALUES
An lvalue (short for “left value” or “locator value”, and sometimes written as “l-value”) is an expression that evaluates to an identifiable object or function (or bit-field).

An rvalue (short for “right value”, and sometimes written as r-value) is an expression that is not an l-value. Commonly seen rvalues include literals (except C-style string literals, which are lvalues) and the return value of functions and operators. Rvalues aren’t identifiable (meaning they have to be used immediately), and only exist within the scope of the expression in which they are used.

lvalues will implicitly convert to rvalues, so an lvalue can be used wherever an rvalue is required.

As a rule of thumb to identify lvalue and rvalue expressions:

lvalues expressions are those that evaluate to variables or other identifiable objects that persist beyond the end of the expression.
rvalues expressions are those that evaluate to literals or the returned value of functions and operators that are discarded at the end of the expression.

### L-VALUE REFERENCE
Commonly just called a reference since prior to C++11 there was only one type of reference) acts as an alias for an existing lvalue (such as a variable).

When defining a reference, place the ampersand next to the type (not the reference variable’s name).

When a reference is initialized with an object (or function), we say it is bound to that object (or function). The process by which such a reference is bound is called reference binding. The object (or function) being referenced is sometimes called the referent.

Lvalue references can’t be bound to non-modifiable lvalues or rvalues (otherwise you’d be able to change those values through the reference, which would be a violation of their const-ness).

References can’t be reseated (changed to refer to another object)

When an object being referenced is destroyed before a reference to it, the reference is left referencing an object that no longer exists. Such a reference is called a dangling reference. Accessing a dangling reference leads to undefined behavior.

References aren’t objects

Favor lvalue references to const over lvalue references to non-const unless you need to modify the object being referenced.

Const references bound to temporary objects extend the lifetime of the temporary object

Lvalue references to const can bind to modifiable lvalues, non-modifiable lvalues, and rvalues. This makes them a much more flexible type of reference.

### R-VALUE REFERENCE
Is a reference that is designed to be inintialized with an r-value. It is created using double ampersand "&&". It is ok to write functions that tak r-value reference parameters, but you should almost never return an r-value reference for the same reason you should almost never return an l-value reference. In most cases, you’ll end up returning a dangling reference when the referenced object goes out of scope at the end of the function.

R-value references are more often used as function parameters. This is most useful for function overloads when you want to have different behavior for l-value and r-value arguments.

Named-objects are l-values. Anonymous objects are r-values.

### COPY CONSTRUCTORS AND COPY ASSIGMENT
Copy constructors are used to initialize a class by making a copy of an object of the same class. Copy assignment is used to copy one class object to another existing class object. By default, C++ will provide a copy constructor and copy assignment operator if one is not explicitly provided. These compiler-provided functions do shallow copies, which may cause problems for classes that allocate dynamic memory. So classes that deal with dynamic memory should override these functions to do deep copies.

### MOVE CONSTRUCTORS AND MOVE ASSIGMENT
The goal of the move constructor and move assignment is to move ownership of the resources from one object to another (which is typically much less expensive than making a copy).

Defining a move constructor and move assignment work analogously to their copy counterparts. However, whereas the copy flavors of these functions take a const l-value reference parameter, the move flavors of these functions use non-const r-value reference parameters.

When implementing move semantics, it is important to ensure the moved-from object is left in a valid state, so that it will destruct properly (without creating undefined behavior).

Automatic l-values returned by value may be moved instead of copied. The C++ specification has a special rule that says automatic objects returned from a function by value can be moved even if they are l-values. 

*SIDE NOTES*: 
- If we construct an object or do an assignment where the argument is an l-value, the only thing we can reasonably do is copy the l-value. We can’t assume it’s safe to alter the l-value, because it may be used again later in the program. If we have an expression “a = b”, we wouldn’t reasonably expect b to be changed in any way.

- However, if we construct an object or do an assignment where the argument is an r-value, then we know that r-value is just a temporary object of some kind. Instead of copying it (which can be expensive), we can simply transfer its resources (which is cheap) to the object we’re constructing or assigning. This is safe to do because the temporary will be destroyed at the end of the expression anyway, so we know it will never be used again!

- You can use the delete keyword to disable copy semantics for classes you create by deleting the copy constructor and copy assignment operator.

- std::move allows you to treat an l-value as r-value. This is useful when we want to invoke move semantics instead of copy semantics on an l-value.

- std::move_if_noexcept will return a movable r-value if the object has a noexcept move constructor, otherwise it will return a copyable l-value. We can use the noexcept specifier in conjunction with std::move_if_noexcept to use move semantics only when a strong exception guarantee exists (and use copy semantics otherwise).


**[Back to top](#table-of-contents)**

## Project Status
// TODO

**[Back to top](#table-of-contents)**

## Getting Started
// TODO

### Dependencies
// TODO

### Getting the Source

Include a link to your GitHub repository (you have no idea how people will find your code), and also a summary of how to clone.

### Installation
// TODO

### Usage
// TODO

**[Back to top](#table-of-contents)**
## Further Reading
// TODO

**[Back to top](#table-of-contents)**

## License
// TODO

**[Back to top](#table-of-contents)**

## Authors

* **[Antonio Perez](https://github.com/jsueprez)** - *Initial work* -
Source : https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/

Also see the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

**[Back to top](#table-of-contents)**