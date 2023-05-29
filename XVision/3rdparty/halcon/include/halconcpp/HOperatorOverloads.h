/*****************************************************************************
 * HOperatorOverloads.h
 ***************************************************************************** 
 *
 * Project:     HALCON/C++
 * Description: C++ operator overloads for common class operations
 *
 * (c) 2010-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 *
 *****************************************************************************/

#ifndef HCPP_OPERATOR_OVERLOADS_H
#define HCPP_OPERATOR_OVERLOADS_H


namespace HalconCpp
{


/*****************************************************************************
 * HImage: Gray value operations
 *****************************************************************************/
 
// Add gray values
LIntExport HImage operator + (const HImage& image1, const HImage& image2);

// Subtract gray values
LIntExport HImage operator - (const HImage& image1, const HImage& image2);

// Multiply gray values
LIntExport HImage operator * (const HImage& image1, const HImage& image2);

// Shift gray values
LIntExport HImage operator + (const HImage& image, double add);

// Shift gray values
LIntExport HImage operator - (const HImage& image, double sub);

// Scale gray values
LIntExport HImage operator * (const HImage& image, double mult);

// Scale gray values
LIntExport HImage operator / (const HImage& image, double div);

// Shift gray values
LIntExport HImage operator + (double add, const HImage& image);

// Scale gray values
LIntExport HImage operator * (double mult, const HImage& image);


/*****************************************************************************
 * HImage: Segmentation
 *****************************************************************************/

// Dynamic Threshold
LIntExport HRegion operator >= (const HImage& image1, const HImage& image2);

// Dynamic Threshold
LIntExport HRegion operator <= (const HImage& image1, const HImage& image2);

// Fixed Threshold
LIntExport HRegion operator >= (const HImage& image, double threshold);

// Fixed Threshold
LIntExport HRegion operator <= (const HImage& image, double threshold);

// Fixed Threshold
LIntExport HRegion operator >= (double threshold, const HImage& image);

// Fixed Threshold
LIntExport HRegion operator <= (double threshold, const HImage& image);


/*****************************************************************************
 * HImage: Miscellaneous
 *****************************************************************************/

// Reduce domain of image
LIntExport HImage operator & (const HImage& image, const HRegion& region);



/*****************************************************************************
 * HRegion: Sets                                                              *
 *****************************************************************************/

// Intersection of regions
LIntExport HRegion operator & (const HRegion& region1, const HRegion& region2);

// Union of regions
LIntExport HRegion operator | (const HRegion& region1, const HRegion& region2);

// Difference of regions
LIntExport HRegion operator / (const HRegion& region1, const HRegion& region2);

// Intersection of region with image domain
LIntExport HRegion operator & (const HRegion& region, const HImage& image);

// Test if one region is a subset of the other
LIntExport bool   operator >= (const HRegion& region1, const HRegion& region2);

// Test if one region is a subset of the other
LIntExport bool   operator <= (const HRegion& region1, const HRegion& region2);


/*****************************************************************************
 * HRegion: Morphology                                                        *
 *****************************************************************************/

// Minkowski addition of regions
LIntExport HRegion operator + (const HRegion& region1, const HRegion& region2);

// Minkowski substraction of regions
LIntExport HRegion operator - (const HRegion& region1, const HRegion& region2);

// Dilation of region by specified radius
LIntExport HRegion operator + (const HRegion& region, double radius);

// Erosion of region by specified radius
LIntExport HRegion operator - (const HRegion& region, double radius);

// Scaling of region by specified factor
LIntExport HRegion operator * (const HRegion& region, double factor);

// Dilation of region by specified radius
LIntExport HRegion operator + (double radius, const HRegion& region);

// Scaling of region by specified radius
LIntExport HRegion operator * (double factor, const HRegion& region);



/*****************************************************************************
 * HFunction1D
 *****************************************************************************/

// Add a constant offset to the function's Y values
LIntExport HFunction1D operator + (const HFunction1D& function, double add);

// Add a constant offset to the function's Y values
LIntExport HFunction1D operator + (double add, const HFunction1D& function);

// Subtract a constant offset from the function's Y values
LIntExport HFunction1D operator - (const HFunction1D& function, double sub);

// Scale the function's Y values</summary>
LIntExport HFunction1D operator * (const HFunction1D& function, double factor);

// Scale the function's Y values</summary>
LIntExport HFunction1D operator * (double factor, const HFunction1D& function);

// Scale the function's Y values</summary>
LIntExport HFunction1D operator / (const HFunction1D& function, double div);

// Compose two functions (not a pointwise multiplication)</summary>
LIntExport HFunction1D operator * (const HFunction1D& function1, const HFunction1D& function2);



/*****************************************************************************
 * HMatrix
 *****************************************************************************/
 
// Add two matrices
LIntExport HMatrix operator + (const HMatrix& matrix1, const HMatrix& matrix2);

// Subtract two matrices
LIntExport HMatrix operator - (const HMatrix& matrix1, const HMatrix& matrix2);

// Matrix multiplication
LIntExport HMatrix operator * (const HMatrix& matrix1, const HMatrix& matrix2);

// Scale matrix
LIntExport HMatrix operator * (const HMatrix& matrix, double factor);

// Scale matrix
LIntExport HMatrix operator * (double factor, const HMatrix& matrix);

// Solve linear system matrix2 * x = matrix1
LIntExport HMatrix operator / (const HMatrix& matrix1, const HMatrix& matrix2);



/*****************************************************************************
 * HQuaternion
 *****************************************************************************/
 
// Compose two quaternions
LIntExport HQuaternion operator * (const HQuaternion& left, const HQuaternion& right);

/*****************************************************************************
 * HDualQuaternion
 *****************************************************************************/
 
// Compose two dual quaternions
LIntExport HDualQuaternion operator * (const HDualQuaternion& left, const HDualQuaternion& right);



}

#endif
