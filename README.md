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

### R-VALUE REFERENCE
Is a reference that is designed to be inintialized with an r-value. It is created using double ampersand "&&". It is ok to write functions that tak r-value reference parameters, but you should almost never return an r-value reference for the same reason you should almost never return an l-value reference. In most cases, you’ll end up returning a hanging reference when the referenced object goes out of scope at the end of the function.

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

Also see the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

**[Back to top](#table-of-contents)**