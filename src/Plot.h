#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Widget.h"


struct Serie
{
    using SeriePoint = std::pair<double, double>;
    using SerieData = std::vector<SeriePoint>;

    void SetYRange(double min, double max);
    void SetXRange(double min, double max);
    void AddData(double xVal, double yVal);

    std::vector<SeriePoint> serieData;
    double xMin{0};
    double xMax{0};
    double yMin{0};
    double yMax{0};
    bool autorange{true};
};

class Plot : public Widget
{
public:
    Plot() = default;
    Plot(const Plot& other) = default;
    Plot(Plot&& other) = default;
    Plot& operator=(const Plot& other) = default;
    Plot& operator=(Plot&& other) = default;
    ~Plot() override = default;

    void AddSerieData(const std::string& seriesName, double xVal, double yVal);
    Serie& getSeries(const std::string& seriesName);
    void Draw() override;
    void ProcessEvent(const SDL_Event& ev) override;

private:
    void PreparePlotData();

    SDLRect srcPlotRect;
    SDLRect dstPlotRect;

    //using Serie = std::pair<std::string, SerieData>;
    std::unordered_map<std::string, Serie> series;
    std::unordered_map<std::string, std::pair<double, double>> seriesRanges;
    std::vector<double> xValues;
    std::shared_ptr<SDLTexture> plotTexture;
};
