#include "VideoWindow.h"
#include "MainWindow.h"
#include <QFileDialog>

using namespace std;
using namespace cv;

VideoWindow::VideoWindow(WindowImagesInterface *windowImages, QWidget *parent = 0) :
    _windowImages(windowImages)
{
    setupUi(this);

	setAttribute( Qt::WA_DeleteOnClose );

    connect( openFileButton, SIGNAL( clicked() ), this, SLOT( openFileClicked() ) );
    connect( frameSlider, SIGNAL( sliderMoved() ), this, SLOT( openFileClicked() ) );
}

VideoWindow::~VideoWindow()
{
}

void VideoWindow::openFileClicked()
{
	QFileDialog dialog(NULL);
	if ( dialog.exec() ) 
	{
		printf("teste: %s\n", dialog.selectedFiles()[0].toLatin1().data());

        VideoCapture *cap = new VideoCapture(dialog.selectedFiles()[0].toLatin1().data());
        _cap = std::shared_ptr<cv::VideoCapture>(cap);
        double count = _cap->get(CV_CAP_PROP_FRAME_COUNT);
        frameSlider->setMaximum(count);

		Mat image;
		image = imread( dialog.selectedFiles()[0].toLatin1().data(), 1 );
		if ( !image.data )
		{
			printf("No image data \n");
			return;
		}
		_windowImages->setSrcImage(image);
	}
}

void VideoWindow::sliderMoved(int value)
{
    printf("%d", value);

    _cap->set(CV_CAP_PROP_POS_FRAMES, value - 1); //Set index to last frame
    Mat frame;
    bool success = _cap->read(frame); 
	_windowImages->setSrcImage(frame);
}