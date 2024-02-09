# Test script for stepping through creation of a Python object in Boost Python
from polymorphism_ext import *

#input("Press enter")
# a = create_as_shared_A(1)
# print(type(a))
b = create_as_shared_B()
# print(type(b))
# print(b.hello())
sink_shared_A(b)

# b_as_a = create_as_A(1)
# print(type(b_as_a))
# sink_A(b_as_a)
b_as_b = create_as_B()
print(type(b_as_b))
sink_A(b_as_b)
