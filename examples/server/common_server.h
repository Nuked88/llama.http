// Various helper functions and utilities

#pragma once

#include "llama.h"

#include <string>
#include <vector>
#include <random>
#include <thread>
#include <unordered_map>
#include <regex>
//
// CLI argument parsing
//

struct gpt_params {
    int32_t seed          = -1;   // RNG seed
    int32_t n_threads     = std::min(4, (int32_t) std::thread::hardware_concurrency());
    int32_t n_predict     = 128;  // new tokens to predict
    int32_t repeat_last_n = 64;   // last n tokens to penalize
    int32_t n_ctx         = 512;  // context size
    int32_t n_batch       = 8;    // batch size for prompt processing
    int32_t n_keep        = 0;    // number of tokens to keep from initial prompt
    int32_t n_gpu_layers  = 0; // number of layers to store in VRAM
    int32_t main_gpu      = 0;    // the GPU that is used for scratch and small tensors
    float   tensor_split[LLAMA_MAX_DEVICES] = {0}; // how split tensors should be distributed across GPUs

    // sampling parameters
    std::unordered_map<llama_token, float> logit_bias; // logit bias for specific tokens
    int32_t top_k = 40;
    int32_t server_port = 8080; //server port
    float   top_p = 0.95f;
    float   tfs_z             = 1.00f; // 1.0 = disabled
    float   temp  = 0.80f;
    float   repeat_penalty  = 1.10f;
    float   typical_p         = 1.00f; // 1.0 = disabled
    float   frequency_penalty = 0.00f; // 0.0 = disabled
    float   presence_penalty  = 0.00f; // 0.0 = disabled
    int     mirostat          = 0;     // 0 = disabled, 1 = mirostat, 2 = mirostat 2.0
    float   mirostat_tau      = 5.00f; // target entropy
    float   mirostat_eta      = 0.10f; // learning rate
  

    std::string model  = "models/lamma-7B/ggml-model.bin"; // model path
    std::string prompt = "";
    std::string input_prefix = ""; // string to prefix user inputs with
    std::string input_suffix = ""; // string to suffix user inputs with
    std::string server_address = "0.0.0.0"; //server address

    std::string lora_adapter = "";  // lora adapter path
    std::string lora_base    = "";  // base model path for the lora adapter

    std::vector<std::string> antiprompt; // string upon seeing which more user input is prompted

    bool memory_f16        = true;  // use f16 instead of f32 for memory kv
    bool random_prompt     = false; // do not randomize prompt if none provided
    bool use_color         = false; // use color to distinguish generations and inputs
    bool interactive       = false; // interactive mode
    bool penalize_nl       = true;  // consider newlines as a repeatable token
    bool embedding         = false; // get only sentence embedding
    bool interactive_start = false; // wait for user input immediately

    bool instruct          = false; // instruction mode (used for Alpaca models)
    bool ignore_eos        = false; // do not stop generating after eos
    bool perplexity        = false; // compute perplexity over the prompt
    bool use_mlock         = false; // use mlock to keep model in memory
    bool mem_test          = false; // compute maximum memory usage
    bool verbose_prompt    = false; // print prompt tokens before generation
    bool server_start      = false; // start http server
    bool use_mmap          = true;  // use mmap for faster loads
};

bool gpt_params_parse(int argc, char ** argv, gpt_params & params);

void gpt_print_usage(int argc, char ** argv, const gpt_params & params);

std::string gpt_random_prompt(std::mt19937 & rng);

//
// Vocab utils
//

std::vector<llama_token> llama_tokenize(struct llama_context * ctx, const std::string & text, bool add_bos);
