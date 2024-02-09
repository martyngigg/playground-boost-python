#include <boost/python.hpp>
#include <iostream>
#include <memory>
#include <string>

using namespace boost;
using namespace boost::python;

struct A {
  virtual ~A() { std::cerr << "~A(): " << this << "\n"; }
  virtual std::string hello() { return "Hello I'm A!"; }
};

struct B : A {
  virtual ~B() { std::cerr << "~B(): " << this << "\n"; }
  std::string hello() { return "Hello I'm B!"; }
};

A *create_as_A(int choice) {
  switch (choice) {
  case 0:
    return new A;
  case 1:
    return new B;
  default:
    return nullptr;
  }
}

B *create_as_B() { return new B; }

void sink_A(const object &obj) {
  A *extracted_ref = extract<A *>(obj)();
  assert(extracted_ref);
  std::cerr << extracted_ref->hello() << "\n";
}

std::shared_ptr<A> create_as_shared_A(int choice) {
  switch (choice) {
  case 0:
    return std::shared_ptr<A>(new A);
  case 1:
    return std::shared_ptr<B>(new B);
  default:
    return std::shared_ptr<A>();
  }
}

std::shared_ptr<B> create_as_shared_B() { return std::shared_ptr<B>(new B); }

void sink_shared_A(const object &obj) {
  auto extracted_value = extract<std::shared_ptr<A>>(obj)();
  std::cerr << "Extracted val: " << extracted_value
            << ", use_count: " << extracted_value.use_count() << "\n";
  auto extracted_ref = extract<const std::shared_ptr<A> &>(obj)();
  std::cerr << "Extracted ref: " << extracted_ref
            << ", use_count: " << extracted_ref.use_count() << "\n";
}

BOOST_PYTHON_MODULE(polymorphism_ext) {
  class_<A>("A", init<>()).def("hello", &A::hello);
  register_ptr_to_python<std::shared_ptr<A>>();
  class_<B, bases<A>>("B", init<>());
  register_ptr_to_python<std::shared_ptr<B>>();

  def("create_as_A", create_as_A, return_value_policy<manage_new_object>());
  def("create_as_B", create_as_B, return_value_policy<manage_new_object>());
  def("sink_A", sink_A);
  def("create_as_shared_A", create_as_shared_A);
  def("create_as_shared_B", create_as_shared_B);
  def("sink_shared_A", sink_shared_A);
}
