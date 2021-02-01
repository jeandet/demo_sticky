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

template <std::size_t count>
std::vector<double> get_data()
{
    static std::ifstream ifs("/dev/ttyACM0", std::ifstream::in);
    std::vector<double> result(count);
    for (auto i = 0UL; i < count; i++)
    {
        ifs >> result[i];
    }
    return result;
}

inline data_t add_index(const std::vector<double>& data)
{
    data_t result { {}, data };
    result.first.resize(std::size(data));
    for (auto i = 0UL; i < std::size(data); i++)
    {
        result.first[i] = i;
    }
    return result;
}

constexpr auto size = 4096 * 8;
using fft_t = FFT::FFT<size, double>;
using namespace channels::operators;
using namespace channels;
using namespace std::placeholders;

int main(int argc, char* argv[])
{

    QApplication app { argc, argv };
    QWidget wdgt;
    wdgt.setLayout(new QVBoxLayout);
    auto spectrum_plot = new SciQLopPlots::SciQLopPlot;
    auto waveform_plot = new SciQLopPlots::SciQLopPlot;
    wdgt.layout()->addWidget(waveform_plot);
    wdgt.layout()->addWidget(spectrum_plot);
    auto spectrum_graph = SciQLopPlots::add_graph<data_t>(spectrum_plot);
    auto waveform_graph = SciQLopPlots::add_graph<data_t>(waveform_plot);


    auto sticky_pipeline =
        [&waveform_graph]() {
            auto data = get_data<size>();
            waveform_graph.add(add_index(data));
            return data;
        }
        >> fft_t::fft >>
        [](const std::vector<std::complex<double>> spect) { return fft_t::mod(spect, true); }
        >> add_index >> spectrum_graph;

    wdgt.setMinimumSize(1024,768);
    wdgt.show();
    return app.exec();
}
