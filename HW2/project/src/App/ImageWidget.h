#pragma once
#include <QWidget>
#include <QtWidgets>
#include <QImage>
#include <QPainter>
#include <vector>

#include "IDW.h"
#include "RBF.h"

QT_BEGIN_NAMESPACE
class QImage;
class QPainter;
QT_END_NAMESPACE

class ImageWidget :
	public QWidget
{
	Q_OBJECT

public:
	ImageWidget(void);
	~ImageWidget(void);

	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);


protected:
	void paintEvent(QPaintEvent* paintevent);

public slots:
	// File IO
	void Open();												// Open an image file, support ".bmp, .png, .jpg" format
	void Save();												// Save image to current file
	void SaveAs();												// Save image to another file

	// Image processing
	void Invert();												// Invert pixel value in image
	void Mirror(bool horizontal = false, bool vertical = true);		// Mirror image vertically or horizontally
	void TurnGray();											// Turn image to gray-scale map
	void Restore();												// Restore image to origin

	void Input();             //Get input data
	void DoIDW();             //do IDW
	void DoRBF();             //do RBF
	void ClearInput();
	void SetInput(bool input);
	void Sethole(bool hole);

private:
	QImage* ptr_image_;				// image 
	QImage* ptr_image_backup_;
	QImage* ptr_tmp;

	std::vector<QPoint> p_, q_;
	int current_point_;
	bool isfill;
	bool is_input_;
	bool isIDW;
	bool isRBF;
};

