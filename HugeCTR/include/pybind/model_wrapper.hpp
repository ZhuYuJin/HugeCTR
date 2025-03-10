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

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <pybind/model.hpp>

namespace HugeCTR {

namespace python_lib {

void ModelPybind(pybind11::module &m) {
  pybind11::class_<HugeCTR::DataReaderParams, std::shared_ptr<HugeCTR::DataReaderParams>>(
      m, "DataReaderParams")
      .def(pybind11::init<DataReaderType_t, std::string, std::string, std::string, Check_t, int,
                          long long, long long, bool, bool, int, std::vector<long long> &,
                          const DataSourceParams &, const AsyncParam &>(),
           pybind11::arg("data_reader_type"), pybind11::arg("source"), pybind11::arg("keyset") = "",
           pybind11::arg("eval_source"), pybind11::arg("check_type"),
           pybind11::arg("cache_eval_data") = 0, pybind11::arg("num_samples") = 0,
           pybind11::arg("eval_num_samples") = 0, pybind11::arg("float_label_dense") = false,
           pybind11::arg("read_file_sequentially") = false, pybind11::arg("num_workers") = 12,
           pybind11::arg("slot_size_array") = std::vector<long long>(),
           pybind11::arg("data_source_params") = new DataSourceParams(),
           pybind11::arg("async_param") =
               AsyncParam{16, 4, 512000, 4, 512, false, Alignment_t::None, false, false})
      .def(pybind11::init<DataReaderType_t, std::vector<std::string>, std::vector<std::string>,
                          std::string, Check_t, int, long long, long long, bool, bool, int,
                          std::vector<long long> &, const DataSourceParams &, const AsyncParam &>(),
           pybind11::arg("data_reader_type"), pybind11::arg("source"),
           pybind11::arg("keyset") = std::vector<std::string>(), pybind11::arg("eval_source"),
           pybind11::arg("check_type"), pybind11::arg("cache_eval_data") = 0,
           pybind11::arg("num_samples") = 0, pybind11::arg("eval_num_samples") = 0,
           pybind11::arg("float_label_dense") = false,
           pybind11::arg("read_file_sequentially") = false, pybind11::arg("num_workers") = 12,
           pybind11::arg("slot_size_array") = std::vector<long long>(),
           pybind11::arg("data_source_params") = new DataSourceParams(),
           pybind11::arg("async_param") =
               AsyncParam{16, 4, 512000, 4, 512, false, Alignment_t::None, false, false});
  pybind11::class_<HugeCTR::Input, std::shared_ptr<HugeCTR::Input>>(m, "Input")
      .def(pybind11::init<int, std::string, int, std::string,
                          std::vector<DataReaderSparseParam> &>(),
           pybind11::arg("label_dim"), pybind11::arg("label_name"), pybind11::arg("dense_dim"),
           pybind11::arg("dense_name"), pybind11::arg("data_reader_sparse_param_array"))
      .def(pybind11::init<std::vector<int>, std::vector<std::string>, int, std::string,
                          std::vector<DataReaderSparseParam> &>(),
           pybind11::arg("label_dims"), pybind11::arg("label_names"), pybind11::arg("dense_dim"),
           pybind11::arg("dense_name"), pybind11::arg("data_reader_sparse_param_array"))
      .def(pybind11::init<std::vector<int>, std::vector<std::string>, std::vector<float>, int,
                          std::string, std::vector<DataReaderSparseParam> &>(),
           pybind11::arg("label_dims"), pybind11::arg("label_names"),
           pybind11::arg("label_weights"), pybind11::arg("dense_dim"), pybind11::arg("dense_name"),
           pybind11::arg("data_reader_sparse_param_array"));
  pybind11::class_<HugeCTR::SparseEmbedding, std::shared_ptr<HugeCTR::SparseEmbedding>>(
      m, "SparseEmbedding")
      .def(pybind11::init<Embedding_t, size_t, size_t, const std::string &, std::string,
                          std::string, std::vector<size_t> &, std::shared_ptr<OptParamsPy> &,
                          const HybridEmbeddingParam &>(),
           pybind11::arg("embedding_type"), pybind11::arg("workspace_size_per_gpu_in_mb") = 0,
           pybind11::arg("embedding_vec_size"), pybind11::arg("combiner"),
           pybind11::arg("sparse_embedding_name"), pybind11::arg("bottom_name"),
           pybind11::arg("slot_size_array") = std::vector<size_t>(),
           pybind11::arg("optimizer") = std::shared_ptr<OptParamsPy>(new OptParamsPy()),
           pybind11::arg("hybrid_embedding_param") =
               HybridEmbeddingParam{1, -1, 0.01, 1.3e11, 2.6e11, 1.0,
                                    hybrid_embedding::CommunicationType::NVLink_SingleNode,
                                    hybrid_embedding::HybridEmbeddingType::Distributed});
  pybind11::class_<HugeCTR::DenseLayerComputeConfig>(m, "DenseLayerComputeConfig")
      .def(pybind11::init<bool, bool>(), pybind11::arg("async_wgrad") = false,
           pybind11::arg("fuse_wb") = false);
  pybind11::class_<HugeCTR::DenseLayer, std::shared_ptr<HugeCTR::DenseLayer>>(m, "DenseLayer")
      .def(pybind11::init<Layer_t, std::vector<std::string> &, std::vector<std::string> &, float,
                          float, Initializer_t, Initializer_t, float, float, size_t, Initializer_t,
                          Initializer_t, int, size_t, size_t, size_t, size_t, size_t, bool,
                          std::vector<int> &, std::vector<std::pair<int, int>> &,
                          std::vector<int> &, std::vector<size_t> &, size_t, size_t, int, int, int,
                          int, bool, std::vector<float> &, bool, Regularizer_t, float, FcPosition_t,
                          Activation_t, std::vector<size_t>, bool, std::vector<Activation_t>,
                          std::vector<bool>, DenseLayerComputeConfig, const std::vector<int64_t> &,
                          int, const std::vector<int64_t> &>(),
           pybind11::arg("layer_type"), pybind11::arg("bottom_names"), pybind11::arg("top_names"),
           pybind11::arg("factor") = 1.0, pybind11::arg("eps") = 0.00001,
           pybind11::arg("gamma_init_type") = Initializer_t::Default,
           pybind11::arg("beta_init_type") = Initializer_t::Default,
           pybind11::arg("dropout_rate") = 0.5, pybind11::arg("elu_alpha") = 1.0,
           pybind11::arg("num_output") = 1,
           pybind11::arg("weight_init_type") = Initializer_t::Default,
           pybind11::arg("bias_init_type") = Initializer_t::Default,
           pybind11::arg("num_layers") = 0, pybind11::arg("leading_dim") = 0,
           pybind11::arg("time_step") = 0, pybind11::arg("batchsize") = 1,
           pybind11::arg("SeqLength") = 1, pybind11::arg("vector_size") = 1,
           pybind11::arg("selected") = false, pybind11::arg("selected_slots") = std::vector<int>(),
           pybind11::arg("ranges") = std::vector<std::pair<int, int>>(),
           pybind11::arg("indices") = std::vector<int>(),
           pybind11::arg("weight_dims") = std::vector<size_t>(),
           pybind11::arg("projection_dim") = 0, pybind11::arg("out_dim") = 0,
           pybind11::arg("axis") = 1, pybind11::arg("max_sequence_len_from") = 1,
           pybind11::arg("max_sequence_len_to") = 1, pybind11::arg("num_attention_heads") = 1,
           pybind11::arg("transpose_b") = false,
           pybind11::arg("target_weight_vec") = std::vector<float>(),
           pybind11::arg("use_regularizer") = false,
           pybind11::arg("regularizer_type") = Regularizer_t::L1, pybind11::arg("lambda") = 0,
           pybind11::arg("pos_type") = FcPosition_t::None,
           pybind11::arg("act_type") = Activation_t::Relu,
           pybind11::arg("num_outputs") = std::vector<size_t>(), pybind11::arg("use_bias") = true,
           pybind11::arg("activations") = std::vector<Activation_t>(),
           pybind11::arg("biases") = std::vector<bool>(),
           pybind11::arg("compute_config") = DenseLayerComputeConfig(),
           pybind11::arg("shape") = std::vector<int64_t>(), pybind11::arg("dim") = 0,
           pybind11::arg("index") = std::vector<int64_t>());

  pybind11::class_<HugeCTR::Model, std::shared_ptr<HugeCTR::Model>>(m, "Model")
      .def(pybind11::init<const Solver &, const DataReaderParams &,
                          std::shared_ptr<OptParamsPy> &>(),
           pybind11::arg("solver"), pybind11::arg("reader_params"), pybind11::arg("opt_params"))
      .def("compile", pybind11::overload_cast<>(&HugeCTR::Model::compile))
      .def("compile",
           pybind11::overload_cast<std::vector<std::string> &, std::vector<float> &>(
               &HugeCTR::Model::compile),
           pybind11::arg("loss_names"), pybind11::arg("loss_weights"))
      .def("summary", &HugeCTR::Model::summary)
      .def("fit", &HugeCTR::Model::fit, pybind11::arg("num_epochs") = 0,
           pybind11::arg("max_iter") = 2000, pybind11::arg("display") = 200,
           pybind11::arg("eval_interval") = 1000, pybind11::arg("snapshot") = 10000,
           pybind11::arg("snapshot_prefix") = "")
      .def("set_source",
           pybind11::overload_cast<std::string, std::string>(&HugeCTR::Model::set_source),
           pybind11::arg("source"), pybind11::arg("eval_source"))
      .def("graph_to_json", &HugeCTR::Model::graph_to_json, pybind11::arg("graph_config_file"))
      .def("construct_from_json", &HugeCTR::Model::construct_from_json,
           pybind11::arg("graph_config_file"), pybind11::arg("include_dense_network"))
      .def("reset_learning_rate_scheduler", &HugeCTR::Model::reset_learning_rate_scheduler,
           pybind11::arg("base_lr"), pybind11::arg("warmup_steps") = 1,
           pybind11::arg("decay_start") = 0, pybind11::arg("decay_steps") = 1,
           pybind11::arg("decay_power") = 2.f, pybind11::arg("end_lr") = 0.f)
      .def("freeze_embedding", pybind11::overload_cast<>(&HugeCTR::Model::freeze_embedding))
      .def("freeze_embedding",
           pybind11::overload_cast<const std::string &>(&HugeCTR::Model::freeze_embedding),
           pybind11::arg("embedding_name"))
      .def("freeze_dense", &HugeCTR::Model::freeze_dense)
      .def("unfreeze_embedding", pybind11::overload_cast<>(&HugeCTR::Model::unfreeze_embedding))
      .def("unfreeze_embedding",
           pybind11::overload_cast<const std::string &>(&HugeCTR::Model::unfreeze_embedding),
           pybind11::arg("embedding_name"))
      .def("unfreeze_dense", &HugeCTR::Model::unfreeze_dense)
      .def("load_dense_weights", &HugeCTR::Model::load_dense_weights,
           pybind11::arg("dense_model_file"))
      .def("load_sparse_weights",
           pybind11::overload_cast<const std::vector<std::string> &>(
               &HugeCTR::Model::load_sparse_weights),
           pybind11::arg("sparse_embedding_files"))
      .def("load_sparse_weights",
           pybind11::overload_cast<const std::map<std::string, std::string> &>(
               &HugeCTR::Model::load_sparse_weights),
           pybind11::arg("sparse_embedding_files_map"))
      .def("embedding_load",
           pybind11::overload_cast<const std::string &, const std::vector<std::string> &>(
               &HugeCTR::Model::embedding_load),
           pybind11::arg("path"), pybind11::arg("table_names") = std::vector<std::string>())
      .def("embedding_dump",
           pybind11::overload_cast<const std::string &, const std::vector<std::string> &>(
               &HugeCTR::Model::embedding_dump),
           pybind11::arg("path"), pybind11::arg("table_names") = std::vector<std::string>())
      .def("load_dense_optimizer_states", &HugeCTR::Model::load_dense_optimizer_states,
           pybind11::arg("dense_opt_states_file"))
      .def("load_sparse_optimizer_states",
           pybind11::overload_cast<const std::vector<std::string> &>(
               &HugeCTR::Model::load_sparse_optimizer_states),
           pybind11::arg("sparse_opt_states_files"))
      .def("load_sparse_optimizer_states",
           pybind11::overload_cast<const std::map<std::string, std::string> &>(
               &HugeCTR::Model::load_sparse_optimizer_states),
           pybind11::arg("sparse_opt_states_files_map"))
      .def("add", pybind11::overload_cast<Input &>(&HugeCTR::Model::add), pybind11::arg("input"))
      .def("add", pybind11::overload_cast<SparseEmbedding &>(&HugeCTR::Model::add),
           pybind11::arg("sparse_embedding"))
      .def("add", pybind11::overload_cast<DenseLayer &>(&HugeCTR::Model::add),
           pybind11::arg("dense_layer"))
      .def("add", pybind11::overload_cast<const EmbeddingCollectionConfig &>(&HugeCTR::Model::add),
           pybind11::arg("ebc_config"))
      .def("set_learning_rate", &HugeCTR::Model::set_learning_rate, pybind11::arg("lr"))
      .def("train", &HugeCTR::Model::train)
      .def("eval", &HugeCTR::Model::eval)
      .def("start_data_reading", &HugeCTR::Model::start_data_reading)
      .def("get_current_loss",
           [](HugeCTR::Model &self) {
             float loss = 0;
             self.get_current_loss(&loss);
             return loss;
           })
      .def("get_eval_metrics", &HugeCTR::Model::get_eval_metrics)
      .def("save_params_to_files", &HugeCTR::Model::download_params_to_files,
           pybind11::arg("prefix"), pybind11::arg("iter") = 0)
      .def("get_data_reader_train", &HugeCTR::Model::get_train_data_reader)
      .def("get_data_reader_eval", &HugeCTR::Model::get_evaluate_data_reader)
      .def("get_learning_rate_scheduler", &HugeCTR::Model::get_learning_rate_scheduler)
      .def(
          "check_out_tensor",
          [](HugeCTR::Model &self, const std::string &tensor_name, Tensor_t tensor_type) {
            const auto tensor_info_tuple = self.get_tensor_info_by_name(tensor_name, tensor_type);
            float *global_result = new float[std::get<1>(tensor_info_tuple)];
            auto global_result_capsule = pybind11::capsule(global_result, [](void *v) {
              float *vv = reinterpret_cast<float *>(v);
              delete[] vv;
            });
            self.check_out_tensor(tensor_type, std::get<3>(tensor_info_tuple), global_result);
            pybind11::array_t<float> tensor_result(std::get<2>(tensor_info_tuple), global_result,
                                                   global_result_capsule);
            return tensor_result;
          },
          pybind11::arg("tensor_name"), pybind11::arg("tensor_type"));
}

}  // namespace python_lib

}  // namespace HugeCTR
