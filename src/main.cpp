#include <FFT/FFT.hpp>
#include <Graph.hpp>
#include <QApplication>
#include <QCustomPlotWrapper.hpp>
#include <SciQLopPlot.hpp>
#include <channels/pipelines.hpp>
#include <fstream>
#include <functional>
#include <iostream>
#include <thread>

using data_t = std::pair<std::vector<double>, std::vector<double>>;

inline std::vector<double> get_data(std::ifstream &ifs,
                                    std::size_t count = 32768) {
  std::vector<double> result(count);
  for (auto i = 0UL; i < count; i++) {
    ifs >> result[i];
  }
  return result;
}

inline data_t add_index(const std::vector<double> &data) {
  data_t result{{}, data};
  result.first.resize(std::size(data));
  for (auto i = 0UL; i < std::size(data); i++) {
    result.first[i] = i;
  }
  return result;
}

constexpr auto size = 4096*4;
using fft_t = FFT::FFT<size, double>;
using namespace channels::operators;
using namespace channels;

int main(int argc, char *argv[]) {

  QApplication app{argc, argv};

  SciQLopPlots::SciQLopPlot plot;
  plot.setMinimumSize(800, 600);
  auto graph = SciQLopPlots::add_graph<data_t>(&plot);

  std::ifstream ifs("/dev/ttyACM0", std::ifstream::in);
  auto __ = [&ifs]() { return get_data(ifs, size); } >> fft_t::fft >>
            fft_t::mod >> add_index >> graph;

  plot.show();

  return app.exec();
}
