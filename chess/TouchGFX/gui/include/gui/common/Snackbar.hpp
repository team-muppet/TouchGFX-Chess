#ifndef SNACKBAR_HPP
#define SNACKBAR_HPP

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/EasingEquations.hpp>

using namespace touchgfx;

class Snackbar
{
public:
    Snackbar(Container* parentContainer, const uint16_t& bitmapId, int x, int y, int fadeInDuration = 10, int visibleDuration = 50, int fadeOutDuration = 30);
    virtual ~Snackbar();
    void show();

    

protected:
    Container* parentContainer;
    FadeAnimator<Image> image;
    int fadeInDuration;
    int visibleDuration;
    int fadeOutDuration;

    Callback<Snackbar, const FadeAnimator<Image>&> fadeOutAnimationCallback;

    void startFadeOutAnimation();
    void onFadeOutAnimationEnded(const FadeAnimator<Image>& animator);
};

#endif /* SNACKBAR_HPP */
