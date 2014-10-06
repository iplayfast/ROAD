#ifndef AUDIO_FRACTAL_DECODER_WIDGET_GLOBAL_H
#define AUDIO_FRACTAL_DECODER_WIDGET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AUDIO_FRACTAL_DECODER_WIDGET_LIBRARY)
#  define AUDIO_FRACTAL_DECODER_WIDGETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define AUDIO_FRACTAL_DECODER_WIDGETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // AUDIO_FRACTAL_DECODER_WIDGET_GLOBAL_H
