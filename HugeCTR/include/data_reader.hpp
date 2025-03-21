/*
 * Copyright (c) 2023, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <atomic>
#include <common.hpp>
#include <core23/tensor.hpp>
#include <fstream>
#include <gpu_resource.hpp>
#include <io/filesystem.hpp>
#include <resource_managers/resource_manager_ext.hpp>
#include <tensor2.hpp>
#include <utils.hpp>
#include <vector>

namespace HugeCTR {

/**
 * @brief Data reading controller.
 *
 * Control the data reading from data set to embedding.
 * An instance of DataReader will maintain independent
 * threads for data reading (IDataReaderWorker)
 * from dataset to heap. Meanwhile one independent
 * thread consumes the data (DataCollector),
 * and copy the data to GPU buffer.
 */
class IDataReader {
 public:
  virtual ~IDataReader() {}

  virtual TensorScalarType get_scalar_type() const = 0;

  virtual long long read_a_batch_to_device() = 0;
  virtual long long read_a_batch_to_device_delay_release() = 0;
  virtual long long get_current_batchsize_per_device(size_t local_id) = 0;
  virtual long long get_current_batchsize() = 0;
  virtual long long get_full_batchsize() const = 0;
  virtual bool current_batch_incomplete() const = 0;
  virtual void ready_to_collect() = 0;
  virtual bool is_started() const = 0;
  virtual void start() = 0;

#ifndef DISABLE_CUDF
  virtual void create_drwg_parquet(
      std::string file_list, bool strict_order_of_batches, const std::vector<long long> slot_offset,
      bool start_reading_from_beginning = true, long long max_samples_per_group = 0,
      // label_dense_dim + fixed_slot_dims + variable_slot_id.size() == all columns
      int label_dense_num = 0, int label_dense_dim = 0) = 0;
#endif

  // TODO(xiaoleis, 01182021): add SourceType_t to allow user to change the type
  virtual void set_source(std::string file_name = std::string()) = 0;
};

}  // namespace HugeCTR
