
#include <cassert>
#include <iostream>
#include <memory>

#include "geoarrow/geoarrow.hpp"

using namespace geoarrow;
using namespace arrow::hpp;

int main(int argc, char* argv[]) {
  // Holders for array/schema structs
  builder::CArrayFinalizer input;
  builder::CArrayFinalizer output;

  // build ArrowSchema/ArrowArray from arguments as Well-Known Text
  builder::StringArrayBuilder input_builder;
  input_builder.set_metadata("ARROW:extension:name", "geoarrow.wkt");
  for (int i = 1; i < argc; i++) {
    input_builder.write_element(argv[i]);
  }
  input_builder.release(&input.array_data, input.schema);

  // Create the ArrayView, which provides some geo-specific methods
  std::unique_ptr<ArrayView> view(create_view(input.schema));
  view->set_array(&input.array_data);

  // Create a geo-specific builder that can read an ArrayView as input
  ComputeOptions options;
  options.set_bool("null_is_empty", true);
  std::unique_ptr<ComputeBuilder> output_builder(
      create_builder("global_bounds", options));

  // Do the operation
  view->read_meta(output_builder.get());
  view->read_features(output_builder.get());

  // Get the output
  output_builder->release(&output.array_data, output.schema);

  // Print and verify output: struct<xmin, xmax, ymin, ymax, zmin, zmax, mmin,
  // mmax>
  assert(std::string("+s") == output.schema->format);
  assert(output.schema->n_children == output.array_data.n_children);
  assert(output.schema->n_children == 8);

  const double* output_dbl[8];

  for (int64_t j = 0; j < output.schema->n_children; j++) {
    assert(std::string("g") == output.schema->children[j]->format);
    assert(output.array_data.children[j]->n_buffers == 2);
    assert(output.array_data.children[j]->null_count == 0);
    output_dbl[j] = reinterpret_cast<const double*>(
        output.array_data.children[j]->buffers[1]);

    std::cout << output.schema->children[j]->name << "\t";
  }

  for (int64_t i = 0; i < output.array_data.length; i++) {
    std::cout << "\n";
    for (int64_t j = 0; j < output.array_data.n_children; j++) {
      std::cout << output_dbl[j][i] << "\t";
    }
  }

  std::cout << "\n";

  return 0;
}
