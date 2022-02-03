#include "Plot.h"
#include "normalizedvalue.h"


void Serie::SetXRange(double min, double max)
{
    xMin = min;
    xMax = max;
    autorange = false;
}

void Serie::AddData(double xVal, double yVal)
{
    if(xVal < xMin)
    {
        xMin = xVal;
    }
    else if(xVal > xMax)
    {
        xMax = xVal;
    }
    if(yVal < yMin)
    {
        yMin = yVal;
    }
    else if(yVal > yMax)
    {
        yMax = yVal;
    }
    serieData.emplace_back(xVal, yVal);
}

void Serie::SetYRange(double min, double max)
{
    yMin = min;
    yMax = max;
    autorange = false;
}

void Plot::AddSerieData(const std::string& seriesName, double xVal, double yVal)
{
    std::lock_guard<std::mutex> lock(mxWidget);
    Serie& serie = series[seriesName];
    serie.AddData(xVal, yVal);


    cached = false;
}

Serie&Plot::getSeries(const std::string& seriesName)
{
    return series[seriesName];
}


void Plot::Draw()
{
    if(!cached)
    {
        RenderPlotToTexture();
    }
    if(plotTexture)
    {
        srcPlotRect.SetH(GetH());
        srcPlotRect.SetW(GetW());

        dstPlotRect.SetX(GetX());
        dstPlotRect.SetY(GetY());
        dstPlotRect.SetH(GetH());
        dstPlotRect.SetW(GetW());
        sdlRenderer->DrawF(*plotTexture.get(), srcPlotRect, dstPlotRect, rotationAngle);
    }
}

void Plot::ProcessEvent(const SDL_Event& ev)
{

}

void Plot::RenderPlotToTexture()
{
    if(!plotTexture)
    {
        plotTexture = std::make_shared<SDLTexture>(sdlRenderer, GetW(), GetH());
    }
    else
    {
        plotTexture->Clear(bgColor);
    }

    if(boxed)
    {
        sdlRenderer->DrawRectangleOnTextureF(*plotTexture.get(), boxColor, 0, 0, GetW(), GetH());
    }

    for(const std::pair<const std::string, Serie>& sDataPair : series)
    {

        const std::string& seriesName = sDataPair.first;
        const Serie& sData = sDataPair.second;
        for(size_t ind = 0; ind < sData.serieData.size(); ++ind) //const SeriePoint& point : sData)
        {
            const Serie::SeriePoint& point = sData.serieData[ind];
            if(ind+1 < sData.serieData.size())
            {
                const Serie::SeriePoint& nextPoint = sData.serieData[ind+1];
                const double& x1Val = point.first;
                const double& y1Val = point.second;
                const double& x2Val = nextPoint.first;
                const double& y2Val = nextPoint.second;
                NormalizedValue<float> xNorm(sData.xMin, sData.xMax, 0, GetW());
                NormalizedValue<float> yNorm(sData.yMin, sData.yMax, 0, GetH());
                xNorm.set(x1Val);
                float x1Norm = xNorm.getNormalized();
                xNorm.set(x2Val);
                float x2Norm = xNorm.getNormalized();
                yNorm.set(y1Val);
                float y1Norm = yNorm.getNormalized();
                yNorm.set(y2Val);
                float y2Norm = yNorm.getNormalized();

                sdlRenderer->DrawLineOnTextureF(*plotTexture.get(),
                                                sData.color,
                                                x1Norm,
                                                GetH() - y1Norm,
                                                x2Norm,
                                                GetH() - y2Norm);
                cached = true;
            }
        }
    }

}
