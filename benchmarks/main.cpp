#include <CLI/CLI.hpp>
#include <benchmark/benchmark.h>
#include <string>
#include <vector>

namespace {

int global_argc = 0;
char **global_argv = nullptr;

void parse_normal(benchmark::State &state) {
    int option1;
    std::string option2;
    CLI::App app;
    app.add_option("--option1", option1);
    app.add_option("--option2", option2);

    // Perform setup here
    for(auto _ : state) {
        app.parse(global_argc, global_argv);
        benchmark::DoNotOptimize(app);
        benchmark::ClobberMemory();
    }
}

void parse_global(benchmark::State &state) {
    int option1;
    std::string option2;

    CLI::App app;
    app.add_option("--option1", option1);
    app.add_option("--option2", option2);

    // Perform setup here
    for(auto _ : state) {
        auto args = CLI::detail::args();
        app.parse(args.size(), args.data());
    }
}

void get_global_args(benchmark::State &state) {
    // Perform setup here
    for(auto _ : state) {
        benchmark::DoNotOptimize(CLI::detail::args());
    }
}

void simple_main(benchmark::State &state) {
    // Perform setup here
    for(auto _ : state) {
        int option1;
        std::string option2;

        CLI::App app;
        app.add_option("--option1", option1);
        app.add_option("--option2", option2);

        try {
            app.parse(global_argc, global_argv);
        } catch(const CLI::ParseError &e) {
            app.exit(e);
        }
    }
}

}  // namespace

// Register the function as a benchmark
BENCHMARK(simple_main);
BENCHMARK(get_global_args);
BENCHMARK(parse_normal);
BENCHMARK(parse_global);

// Run the benchmark
int main(int argc, char **argv) {
    global_argc = argc;
    global_argv = argv;

    int argc_ = 1;
    benchmark::Initialize(&argc_, argv);
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
}
