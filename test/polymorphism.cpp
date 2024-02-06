#include <boost/python.hpp>
#include <memory>
#include <string>

using namespace boost;
using namespace boost::python;

struct A {
  static std::shared_ptr<A> create() { return std::shared_ptr<A>(new A); }
  std::string hello() { return "Just nod if you can hear me!"; }
};

BOOST_PYTHON_MODULE(polymorphism_ext) {
  class_<A, std::shared_ptr<A>>("A", init<>())
      .def("create", &A::create)
      .staticmethod("create")
      .def("hello", &A::hello);
}
