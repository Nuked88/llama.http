# LLAMA.http

Start a fast ChatGPT-like model on your pc and interact remotely with it via HTTP requests

This is a continuation of the repository https://github.com/Nuked88/alpaca.http and is **NOT** the same as the official server of llama.cpp

~~No performance seems to have been lost, the result is not streamed so it may look like it will take longer but it really isn't~~.
I noticed that there are some performance issues, and i need to investigate on it.


## Get Started

This project support all the models currently supported by the official llama.cpp since this current commit [HERE A LIST](https://github.com/Nuked88/llama.http#description)


Once you've downloaded the model weights and placed them into the same directory as the `server` or `server.exe` executable, run:

```
./server -m <NAMEMODEL> 
```

Another more compplete example which includes GPU usage could be:
```
./server -m <NAMEMODEL> --ctx_size 2048 -ngl 32 -p "A chat between a curious guy called Alex and a wise man called Bob. Bob gives helpful, detailed, and wise answers to Alex questions." --temp 0.8 -b 256 --top_k 40 --top_p 0.9 --n_predict 2048 --threads 8 
```

### Command line arguments supported

The following arguments are supported:
* `-m MODELPATHANDNAME, --model MODELPATHANDNAME` STRING:  Model path and name (es. /models/alpaca.bin).
* `-sp, --server-port N`: Change the default server port (default: 8080). This option only works if the server is started.
* `-sa, --server-address <address>`: Change the default server address (default: 0.0.0.0). This option only works if the server is started.
* `-s SEED, --seed SEED`: Set the RNG seed (default: -1). Use a random seed for values less than or equal to 0.
* `-t N, --threads N`: Set the number of threads to use during computation (default: 8).
* `-p PROMPT, --prompt PROMPT`: Set the prompt to start generation with (default: empty).
* `--random-prompt`: Start with a randomized prompt.
* `--in-prefix STRING`: Set the string to prefix user inputs with (default: "\\n\\n### Instruction:\\n\\n").
* `--in-suffix STRING`: Set the string to suffix user inputs with (default: "\\n\\n### Response:\\n\\n").
* `-f FNAME, --file FNAME`: Set the prompt file to start generation.
* `-n N, --n_predict N`: Set the number of tokens to predict (default: 2048, -1 for infinity).
* `--top_k N`: Set the top-k sampling value (default: 40).
* `--top_p N`: Set the top-p sampling value (default: 0.9).
* `--repeat_last_n N`: Set the number of last tokens to consider for penalize (default: 1).
* `--repeat_penalty N`: Set the penalty for repeating sequences of tokens (default: 1.0).
* `-c N, --ctx_size N`: Set the size of the prompt context (default: 2048).
* `--ignore-eos`: Ignore the end of stream token and continue generating.
* `--memory_f32`: Use f32 instead of f16 for memory key+value.
* `--temp N`: Set the temperature value (default: 0.8).
* `--n_parts N`: Set the number of model parts (default: -1, determined from dimensions).
* `-b N, --batch_size N`: Set the batch size for prompt processing (default: 256).
* `--perplexity`: Compute perplexity over the prompt.
* `--keep`: Set the number of tokens to keep from the initial prompt.
* `-ngl N, --n-gpu-layers N`: Set the number of layers to store in VRAM.
* `-ts SPLIT, --tensor-split SPLIT`: Set how to split tensors across multiple GPUs (comma-separated list of proportions, e.g., 3,1).
* `-mg N, --main-gpu N`: Set the GPU to use for scratch and small tensors.
* `--mtest`: Compute maximum memory usage.
* `--verbose-prompt`: Print the prompt before generation.



## Using Alpaca.http to interact with the GGML Alpaca model

#### Note: llama.http does not handle conversations
It's important to note that llama.http does not handle conversations. This means that you'll need to manage conversations separately in your program. llama.http simply sends requests to the GGML model and returns the responses.This is by-design.

#### Making requests to the server
To interact with the server, If you're using GET, you can simply include the prompt in the URL with the **text** parameter. If you're using POST, you'll need to send a raw request with the prompt in the body.

##### See the [examples](https://github.com/Nuked88/alpaca.http/tree/master/examples) directory which is complety compatible with this project.

#### Response format
The server will return a JSON object with the following fields:

* **created**: The timestamp of when the response was created.
* **model**: The name of the model used to generate the response.
* **output**: The generated text, followed by an [end of text] marker.
* **usage**: An object containing information about how many tokens were used to generate the response.


Here's an example response:

```
{
    "created": 16798385514,
    "model": "ggml-alpaca-13b-q4.bin",
    "output": "Alpacas are members of the camel family and originated in South America, particularly Peru where they were domesticated by indigenous people over 600 years ago for their wool. They have a thick coat that is used to make sweaters or other clothing items such as hats, gloves etc., which are very popular with tourists visiting the country and also in high demand internationally due to its softness and warmth. Alpacas can be found on farms around Peru where they live together peacefully alongside llamas who help protect them from predators such as foxes, coyotes etc., which are common throughout South America\n[end of text]\n",
    "usage": {
        "completion_tokens": 141,
        "prompt_tokens": 8,
        "total_tokens": 149
    }
}
```

The **usage** object includes the following fields:

* **completion_tokens**: The number of tokens used to generate the response.
* **prompt_tokens**: The number of tokens in the prompt.
* **total_tokens**: The total number of tokens used, including the prompt tokens.





## Build Requirements

To use this library, you need to have Boost installed on your system.

### Installing Boost

1. Download the Boost library from https://www.boost.org/users/history/version_1_81_0.html
2. Extract the `boost` folder from the downloaded archive
3. Place the `boost` folder in the root directory of the cloned repository

## Building from Source (MacOS/Linux)


```sh
git clone https://github.com/Nuked88/llama.http.git
cd llama.http

make server
./server
```


## Building from Source (Windows)

- Download and install CMake: <https://cmake.org/download/>
- Download and install `git`. If you've never used git before, consider a GUI client like <https://desktop.github.com/>
- Clone this repo using your git client of choice (for GitHub Desktop, go to File -> Clone repository -> From URL and paste `https://github.com/Nuked88/llama.http` in as the URL)
- Open a Windows Terminal inside the folder you cloned the repository to
- Run the following commands one by one:

```ps1
cmake .
cmake --build . --config Release
```


## Disclaimer

Please note that I am not an expert in C++ and that there may be bugs or gross errors in this library. This library was created with the goal of providing a server that can be interfaced with various programming languages, so even those who are not experts like myself can fully utilize the llama models.

If you encounter any issues or have any suggestions, please feel free to open an issue on the GitHub repository. I will do my best to address them in a timely manner. Thank you for your understanding and support.

## Credit

This combines [llama.cpp](https://github.com/ggerganov/llama.cpp) by Georgi Gerganov. Inspired by [Simon Willison's](https://til.simonwillison.net/llms/llama-7b-m2) getting started guide for LLaMA. [Andy Matuschak](https://twitter.com/andy_matuschak/status/1636769182066053120)'s thread on adapting this to 13B, using fine tuning weights by [Sam Witteveen](https://huggingface.co/samwit/alpaca13B-lora). 
Library used: 
- [BOOST](https://www.boost.org/). 
- [Nlohmann-json library] (https://github.com/nlohmann/json), distributed under the MIT License.


## Disclaimer

I assume no liability on any damage caused by any action described in this readme or otherwise with the use of this code/program.


