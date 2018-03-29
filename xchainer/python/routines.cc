#include "xchainer/python/routines.h"

#include <cstdint>
#include <string>
#include <vector>

#include <nonstd/optional.hpp>

#include "xchainer/array.h"
#include "xchainer/context.h"
#include "xchainer/device.h"
#include "xchainer/error.h"
#include "xchainer/routines/creation.h"
#include "xchainer/routines/logic.h"
#include "xchainer/routines/manipulation.h"
#include "xchainer/routines/math.h"

#include "xchainer/python/array.h"
#include "xchainer/python/array_index.h"
#include "xchainer/python/common.h"
#include "xchainer/python/device.h"
#include "xchainer/python/shape.h"
#include "xchainer/python/strides.h"

namespace xchainer {
namespace python {
namespace internal {

namespace py = pybind11;

void InitXchainerRoutines(pybind11::module& m) {
    // creation routines
    m.def("empty",
          [](py::tuple shape, Dtype dtype, const nonstd::optional<std::string>& device_id) {
              return Array::Empty(ToShape(shape), dtype, GetDevice(device_id)).move_body();
          },
          py::arg("shape"),
          py::arg("dtype"),
          py::arg("device") = nullptr);
    m.def("full",
          [](py::tuple shape, Scalar fill_value, Dtype dtype, const nonstd::optional<std::string>& device_id) {
              return Array::Full(ToShape(shape), fill_value, dtype, GetDevice(device_id)).move_body();
          },
          py::arg("shape"),
          py::arg("fill_value"),
          py::arg("dtype"),
          py::arg("device") = nullptr);
    m.def("full",
          [](py::tuple shape, Scalar fill_value, const nonstd::optional<std::string>& device_id) {
              return Array::Full(ToShape(shape), fill_value, GetDevice(device_id)).move_body();
          },
          py::arg("shape"),
          py::arg("fill_value"),
          py::arg("device") = nullptr);
    m.def("zeros",
          [](py::tuple shape, Dtype dtype, const nonstd::optional<std::string>& device_id) {
              return Array::Zeros(ToShape(shape), dtype, GetDevice(device_id)).move_body();
          },
          py::arg("shape"),
          py::arg("dtype"),
          py::arg("device") = nullptr);
    m.def("ones",
          [](py::tuple shape, Dtype dtype, const nonstd::optional<std::string>& device_id) {
              return Array::Ones(ToShape(shape), dtype, GetDevice(device_id)).move_body();
          },
          py::arg("shape"),
          py::arg("dtype"),
          py::arg("device") = nullptr);
    m.def("empty_like",
          [](const ArrayBodyPtr& a, const nonstd::optional<std::string>& device_id) {
              return Array::EmptyLike(Array{a}, GetDevice(device_id)).move_body();
          },
          py::arg("a"),
          py::arg("device") = nullptr);
    m.def("full_like",
          [](const ArrayBodyPtr& a, Scalar value, const nonstd::optional<std::string>& device_id) {
              return Array::FullLike(Array{a}, value, GetDevice(device_id)).move_body();
          },
          py::arg("a"),
          py::arg("fill_value"),
          py::arg("device") = nullptr);
    m.def("zeros_like",
          [](const ArrayBodyPtr& a, const nonstd::optional<std::string>& device_id) {
              return Array::ZerosLike(Array{a}, GetDevice(device_id)).move_body();
          },
          py::arg("a"),
          py::arg("device") = nullptr);
    m.def("ones_like",
          [](const ArrayBodyPtr& a, const nonstd::optional<std::string>& device_id) {
              return Array::OnesLike(Array{a}, GetDevice(device_id)).move_body();
          },
          py::arg("a"),
          py::arg("device") = nullptr);
    m.def("copy", [](const ArrayBodyPtr& a) { return Copy(Array{a}).move_body(); }, py::arg("a"));

    // logic routines
    m.def("equal",
          [](const ArrayBodyPtr& x1, const ArrayBodyPtr& x2) { return Equal(Array{x1}, Array{x2}).move_body(); },
          py::arg("x1"),
          py::arg("x2"));

    // manipulation routines
    m.def("transpose", [](const ArrayBodyPtr& a) { return Transpose(Array{a}).move_body(); }, py::arg("a"));
    m.def("reshape",
          [](const ArrayBodyPtr& a, py::tuple newshape) { return Reshape(Array{a}, ToShape(newshape)).move_body(); },
          py::arg("a"),
          py::arg("newshape"));
    m.def("reshape",
          [](const ArrayBodyPtr& a, const std::vector<int64_t>& newshape) {
              return Reshape(Array{a}, {newshape.begin(), newshape.end()}).move_body();
          },
          py::arg("a"),
          py::arg("newshape"));
    m.def("broadcast_to",
          [](const ArrayBodyPtr& array, py::tuple shape) { return Array{array}.BroadcastTo(ToShape(shape)).move_body(); },
          py::arg("array"),
          py::arg("shape"));

    m.def("broadcast_to",
          [](const ArrayBodyPtr& array, py::tuple shape) { return Array{array}.BroadcastTo(ToShape(shape)).move_body(); },
          py::arg("array"),
          py::arg("shape"));

    // math routines
    m.def("add",
          [](const ArrayBodyPtr& x1, const ArrayBodyPtr& x2) { return (Array{x1} + Array{x2}).move_body(); },
          py::arg("x1"),
          py::arg("x2"));
    m.def("multiply",
          [](const ArrayBodyPtr& x1, const ArrayBodyPtr& x2) { return (Array{x1} * Array{x2}).move_body(); },
          py::arg("x1"),
          py::arg("x2"));
    m.def("multiply", [](const ArrayBodyPtr& x1, Scalar x2) { return Multiply(Array{x1}, x2).move_body(); }, py::arg("x1"), py::arg("x2"));
    m.def("multiply", [](Scalar x1, const ArrayBodyPtr& x2) { return Multiply(x1, Array{x2}).move_body(); }, py::arg("x1"), py::arg("x2"));
    m.def("sum",
          [](const ArrayBodyPtr& a, int8_t axis, bool keepdims) { return Sum(Array{a}, std::vector<int8_t>{axis}, keepdims).move_body(); },
          py::arg("a"),
          py::arg("axis"),
          py::arg("keepdims") = false);
    m.def("sum",
          [](const ArrayBodyPtr& a, nonstd::optional<std::vector<int8_t>> axis, bool keepdims) {
              return Sum(Array{a}, axis, keepdims).move_body();
          },
          py::arg("a"),
          py::arg("axis") = nullptr,
          py::arg("keepdims") = false);
}

}  // namespace internal
}  // namespace python
}  // namespace xchainer
