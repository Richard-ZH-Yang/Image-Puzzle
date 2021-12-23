#include "block.h"
#include <cmath>
#include <iostream>


// EFFECTS: return the height of the block
int Block::height() const {
  /* your code here */
  if (Block::width() == 0) {
    return 0;
  }
  
  return data[0].size();
}

int Block::width() const {
  /* your code here */
  return data.size();
}


  /**
   * Renders the given block onto img with its upper
   * left corner at (x, 0). Assumes block fits on the 
   * image.
   */
void Block::render(PNG &im, int x) const {

  for (int col = 0; col < Block::width(); col++) {
    for (int row = 0; row < Block::height(); row++) {
      // cout << col << "BLOCK-COL" << endl;
      // cout << row << "BLOCK-ROW" << endl;
      HSLAPixel *pixel = im.getPixel(col + x, row);
      *pixel = data[col][row];

    }

  }


}

  /** 
   * Creates a block that is width X img.height pixels in size
   * by copying the pixels from (x, 0) to (x+width-1, img.height-1)
   * in img. Assumes img is large enough to supply these pixels.
   */
void Block::build(PNG &im, int x, int width) {
    /* your code here */
  int height = (int)im.height();
  vector<vector<HSLAPixel>> data666(width, vector<HSLAPixel>(height));

  for (int col = 0; col < width; col++) {
    for (int row = 0; row < height; row++) {
      HSLAPixel *curr = im.getPixel(col + x, row);

      data666[col][row] = *curr;

    }
  }

  data = data666;
  
}


