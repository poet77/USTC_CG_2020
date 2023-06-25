#include "Poisson.h"
#include <time.h>
#include <iostream>

CPoissonEdit::CPoissonEdit(void)
	:source_imagewidget_(NULL),target_imagewidget_(NULL),source_rect_region_(NULL),source_inside_points_(NULL),
	inside_points_count_(0)
{
}


CPoissonEdit::~CPoissonEdit(void)
{
}

//Initializes the loaded image

void CPoissonEdit::init(ImageWidget *src_imgwdg, ImageWidget *tar_imgwdg)
{
	inside_points_count_ = 0;
	source_imagewidget_ = src_imgwdg;
	target_imagewidget_ = tar_imgwdg;

	source_rect_region_ = &(source_imagewidget_->rect_or_ellipse_);
	source_inside_points_ = &(source_imagewidget_->inside_points_);

	poissoned_rgb_.resize(source_width(),source_height());
	coor_to_index_.resize(source_width(),source_height());
	index_to_coor_.clear();
	
	for (int i=0;i<source_width();i++)
		for (int j=0;j<source_height();j++)
			if (1 == (*source_inside_points_)(i,j))
			{
				coor_to_index_(i,j) = inside_points_count_++;
				index_to_coor_.push_back(QPoint(i,j));
			}
	if (inside_points_count_)
		buildAMat();
}

// Get the width of source image

int CPoissonEdit::source_width()
{
	return source_imagewidget_->width();
}

// Get the height of source image

int CPoissonEdit::source_height()
{
	return source_imagewidget_->height();
}

// Construct the sparse matrix A

void CPoissonEdit::buildAMat()
{

	A_.resize(inside_points_count_,inside_points_count_);

	std::vector<Eigen::Triplet<double> > coefficients;
	for (int i=0;i<inside_points_count_;i++)
	{
		QPoint coor = index_to_coor_[i];
		int x = coor.x();
		int y = coor.y();
		int np = 4;
		if (x == 0 || x == source_width() - 1)
			np--;
		if (y == 0 || y == source_height() -1)
			np--;
		coefficients.push_back(Eigen::Triplet<double>(i,i,np));

		if (x>0 && (*source_inside_points_)(x-1,y) == 1)
			coefficients.push_back(Eigen::Triplet<double>(i,coor_to_index_(x-1,y),-1));
		if (x<source_width()-1 && (*source_inside_points_)(x+1,y) == 1)
			coefficients.push_back(Eigen::Triplet<double>(i,coor_to_index_(x+1,y),-1));
		if (y>0 && (*source_inside_points_)(x,y-1) == 1)
			coefficients.push_back(Eigen::Triplet<double>(i,coor_to_index_(x,y-1),-1));
		if (y<source_height()-1 && (*source_inside_points_)(x,y+1) == 1)
			coefficients.push_back(Eigen::Triplet<double>(i,coor_to_index_(x,y+1),-1));
	}

	A_.setFromTriplets(coefficients.begin(),coefficients.end());

	LLT_.compute(A_);   //solve by LLT

}

// Get the image by Poisson

Eigen::MatrixXi CPoissonEdit::GetPoissonedImage(int xpos, int ypos)
{
	// Show computing time
    clock_t start,end1,end2,end3;
    start=clock();
	if (!inside_points_count_)
		return poissoned_rgb_;
	buildbMat(xpos,ypos);
    end1=clock();
	Eigen::MatrixX3d X;
	X = LLT_.solve(b_); //solve by LLT
    end2=clock();
	// Make sure the RGB value is at [0,255] 
	for (int i=0;i<inside_points_count_;i++)
	{
		QPoint coor = index_to_coor_[i];
		int r,g,b;
		r = (int)X(i,0);
		r = (r<0)?0:r;
		r = (r>255)?255:r;
		g = (int)X(i,1);
		g = (g<0)?0:g;
		g = (g>255)?255:g;
		b = (int)X(i,2);
		b = (b<0)?0:b;
		b = (b>255)?255:b;
		poissoned_rgb_(coor.x(),coor.y()) = qRgb(r,g,b);
	}
    end3=clock();
	// Show the time spent
    double endtime1=(double)(end1-start)/CLOCKS_PER_SEC;
    double endtime2=(double)(end2-end1)/CLOCKS_PER_SEC;
    double endtime3=(double)(end3-end2)/CLOCKS_PER_SEC;
    std::cout<<"Get"<<endtime1<<" "<<endtime2<<" "<<endtime3<<std::endl;
	return poissoned_rgb_;
}

//Construct the matrix B

void CPoissonEdit::buildbMat(int xpos, int ypos)
{
    clock_t start,end1,end2,end3;
    start=clock();
	QPoint delta[4] = {QPoint(-1,0),QPoint(1,0),QPoint(0,-1),QPoint(0,1)};
	b_ = Eigen::MatrixX3d::Zero(inside_points_count_,3);
    end1=clock();
	for (int i=0;i<inside_points_count_;i++)
	{
        end2=clock();
		QPoint coor = index_to_coor_[i];
		int x = coor.x();
		int y = coor.y();

		for (int j=0;j<4;j++)
		{
			QPoint q = coor + delta[j];
			if (q.x()>=0 && q.x()<source_width() && q.y()>=0 && q.y()<source_height())
			{
				b_(i,0) += v(coor,q,0,QPoint(xpos,ypos));
				b_(i,1) += v(coor,q,1,QPoint(xpos,ypos));
				b_(i,2) += v(coor,q,2,QPoint(xpos,ypos));
				if ( 2== (*source_inside_points_)(q.x(),q.y()))
				{
                    b_(i,0) += qRed(target_imagewidget_->image().pixel(q-source_rect_region_->topLeft()+QPoint(xpos,ypos)));
                    b_(i,1) += qGreen(target_imagewidget_->image().pixel(q-source_rect_region_->topLeft()+QPoint(xpos,ypos)));
                    b_(i,2) += qBlue(target_imagewidget_->image().pixel(q-source_rect_region_->topLeft()+QPoint(xpos,ypos)));
				}
			}
		}
	}
	// Show the time spent
    end2=clock();
    double endtime1=(double)(end1-start)/CLOCKS_PER_SEC;
    double endtime2=(double)(end2-end1)/CLOCKS_PER_SEC;
    //double endtime3=(double)(end3-end2)/CLOCKS_PER_SEC;
    std::cout<<"buildmap"<<endtime1<<" "<<endtime2<<std::endl;
}
