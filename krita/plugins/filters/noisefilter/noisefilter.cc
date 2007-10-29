/*
 * This file is part of the KDE project
 *
 * Copyright (c) 2005 Cyrille Berger <cberger@cberger.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "noisefilter.h"

#include <stdlib.h>
#include <vector>

#include <qpoint.h>

#include <kdebug.h>
#include <kiconloader.h>
#include <kcomponentdata.h>
#include <kgenericfactory.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <knuminput.h>
#include <kstandarddirs.h>

#include <kis_image.h>
#include <kis_paint_device.h>
#include <kis_iterators_pixel.h>
#include <kis_layer.h>
#include <kis_filter_registry.h>
#include <kis_global.h>
#include <kis_types.h>

#include "kis_wdg_noise.h"
#include "ui_wdgnoiseoptions.h"

typedef KGenericFactory<KritaNoiseFilter> KritaNoiseFilterFactory;
K_EXPORT_COMPONENT_FACTORY( kritanoisefilter, KritaNoiseFilterFactory( "krita" ) )

KritaNoiseFilter::KritaNoiseFilter(QObject *parent, const QStringList &)
        : KParts::Plugin(parent)
{
    setComponentData(KritaNoiseFilterFactory::componentData());


    if (parent->inherits("KisFilterRegistry")) {
        KisFilterRegistry * manager = dynamic_cast<KisFilterRegistry *>(parent);
        manager->add(KisFilterSP(new KisFilterNoise()));
    }
}

KritaNoiseFilter::~KritaNoiseFilter()
{
}

KisFilterNoise::KisFilterNoise() : KisFilter(id(), CategoryOther, i18n("&Random Noise..."))
{
}

KisFilterConfiguration* KisFilterNoise::factoryConfiguration(const KisPaintDeviceSP)
{
    KisFilterConfiguration* config = new KisFilterConfiguration("noise", 1);
    config->setProperty("level", 50 );
    config->setProperty("opacity", 100 );
    return config;
}

KisFilterConfigWidget * KisFilterNoise::createConfigurationWidget(QWidget* parent, KisPaintDeviceSP dev)
{
    Q_UNUSED(dev);
    return new KisWdgNoise((KisFilter*)this, (QWidget*)parent);
}

void KisFilterNoise::process(KisFilterConstantProcessingInformation src,
                 KisFilterProcessingInformation dst,
                 const QSize& size,
                 const KisFilterConfiguration* config,
                 KoProgressUpdater* progressUpdater
        ) const
{
#if 0
    Q_ASSERT(src != 0);
    Q_ASSERT(dst != 0);

    setProgressTotalSteps(size.width() * size.height());

    KoColorSpace * cs = src->colorSpace();

    QVariant value;
    int level = (config && config->getProperty("level", value)) ? value.toInt() : 50;
    int opacity = (config && config->getProperty("opacity", value)) ? value.toInt() : 100;

    KisRectIteratorPixel dstIt = dst->createRectIterator(dstTopLeft.x(), dstTopLeft.y(), size.width(), size.height() );
    KisRectConstIteratorPixel srcIt = src->createRectConstIterator(srcTopLeft.x(), srcTopLeft.y(), size.width(), size.height());

    quint8* interm = new quint8[ cs->pixelSize() ];
    qint32 threshold = (RAND_MAX / 100) * (100 - level);

    quint8 weights[2];
    weights[0] = (255 * opacity) / 100; weights[1] = 255 - weights[0];
    const quint8* pixels[2];
    pixels[0] = interm;

    KoMixColorsOp * mixOp = cs->mixColorsOp();

    while(!srcIt.isDone())
    {
        if(rand() > threshold)
        {
            // XXX: Added static_cast to get rid of warnings
            QColor c = qRgb(static_cast<int>((double)rand()/RAND_MAX * 255),
                            static_cast<int>((double)rand()/RAND_MAX * 255),
                            static_cast<int>((double)rand()/RAND_MAX * 255));
            cs->fromQColor( c, interm, 0 );
            pixels[1] = srcIt.oldRawData();
            mixOp->mixColors( pixels, weights, 2, dstIt.rawData() );
        }
        ++srcIt;
        ++dstIt;
        incProgress();
    }

    delete [] interm;
    setProgressDone(); // Must be called even if you don't really support progression
#endif
}

