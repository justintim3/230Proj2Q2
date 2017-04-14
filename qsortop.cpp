extern int THRESHOLD2;
// Insertion sort for final cleanup sort pass
template <typename E>
inline void inssort4(E A[], int n) { // Insertion Sort
  for (int i=1; i<n; i++)       // Insert i'th record
	  for (int j = i; (j > 0) && (A[j - 1] > A[j]); j--)
	  {
		  E temp = A[j];
		  A[j] = A[j - 1];
		  A[j - 1] = temp;
	  }
}

// qsort core function: do not qsort lists of length <= THRESHOLD2,
// no function calls and no recursion
template <typename E>
void qsortop(E array[], int i, int j) {
  static int stack[200];
  int top = -1;
  E pivot;
  int pivotindex, l, r;

  stack[++top] = i;
  stack[++top] = j;

  while (top > 0) {
    // Pop stack
    j = stack[top--];
    i = stack[top--];

    // Findpivot
    pivotindex = (i+j)/2;
    pivot = array[pivotindex];
	E temp = array[pivotindex];
	array[pivotindex] = array[j];
	array[j] = temp;

    // Partition
    l = i-1;
    r = j;
    do {
      while (pivot > array[++l]);
      while (r && array[--r] > pivot);
	  {
		  E temp = array[l];
		  array[l] = array[r];
		  array[r] = temp;
	  }
    } while (l < r);

	temp = array[l];
	array[l] = array[r];
	array[r] = temp;
	temp = array[l];
	array[l] = array[j];
	array[j] = temp;

    // Load up stack.  l is pivot point.
    if ((l-1-i) > THRESHOLD2) {
      stack[++top] = i;
      stack[++top] = l-1;
    }
    if ((j-l-1) > THRESHOLD2) {
      stack[++top] = l+1;
      stack[++top] = j;
    }
  }
}

template <typename E>
void qsortO(E* array, int n) {
  qsortop<E>(array, 0, n-1);
  inssort4<E>(array, n);      // Final Insertion Sort
}