#include "include/internal/packed_vector.hpp"
//#include "inlcude/internal/spsi.hpp"
#include <dynamic.hpp>
//#include "include/internal/packed_array.hpp"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <malloc.h>

using namespace std;
using namespace dyn;

int main() {
   //mallopt( M_TRIM_THRESHOLD, 1 ); //does not affect anything
   //mallopt( M_MMAP_THRESHOLD, 1 ); 
   
   packed_spsi sp;
   
   sp.insert( 0, 0 );

   sp.insert(1, 18);
   sp.insert(2, 28);
   sp.insert(3, 32);
   sp.insert(4, 3);
   sp.insert(5,120);
   
   for (size_t i = 0; i < sp.size(); ++i) {
      cout << i << ' ' << sp[i] << endl;
   }

   cout << "bitsize (spsi): " << sp.bit_size() << endl;
   
   cout << "sum (spsi): " << sp.psum() << endl;

   size_t n_ops = 1000000;
   srand( time( NULL ) );
   using std::chrono::high_resolution_clock;
   using std::chrono::duration_cast;
   using std::chrono::duration;

   size_t sum = 201;

   cout << "insert (spsi) ... " << flush;
   auto t5 = high_resolution_clock::now();
   for (size_t i = 0; i < n_ops; ++i) {
      //random insertion
      size_t pos = rand() % ( sp.size() + 1 );
      
      sp.insert( pos, rand() );
   }
   auto t6 = high_resolution_clock::now();
   cout << "done." << endl;

   cout << "Size of spsi: " << sp.size() << endl;
   cout << "bitsize (spsi): " << sp.bit_size() << endl;
   //cout << "checking access..." << flush;
   //   auto t5 = high_resolution_clock::now();
   // for (size_t i = 0; i < n_ops; ++i) {
   //    //random insertion
   //    size_t pos = rand() % (v.size());
   //    if ( sp[pos] != v[ pos ] ) {
   // 	 cout << "access failed" << endl;
   // 	 return 1;
   //    }
   // }
   //auto t6 = high_resolution_clock::now();
   //cout << "skipped" << endl;

   cout << "sum (spsi): " << sp.psum() << endl;
   
   cout << "remove (spsi) ... " << flush;
   auto t7 = high_resolution_clock::now();
   for (size_t i = 0; i < n_ops; ++i) {
      //random insertion
      size_t pos = rand() % ( sp.size() );
      sp.remove( pos );
   }

   auto t8 = high_resolution_clock::now();
   cout << "done." << endl;

   cout << "insert2 (spsi) ... " << flush;
   auto t1 = high_resolution_clock::now();
   for (size_t i = 0; i < n_ops; ++i) {
      //random insertion
      size_t pos = rand() % ( sp.size() + 1 );
      
      sp.insert( pos, rand() );
   }
   auto t2 = high_resolution_clock::now();
   cout << "done." << endl;

   uint64_t sec_insert_2 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
   uint64_t sec_spsi_insert = std::chrono::duration_cast<std::chrono::microseconds>(t6 - t5).count();
   uint64_t sec_spsi_remove = std::chrono::duration_cast<std::chrono::microseconds>(t8 - t7).count();

   cout << (double)sec_spsi_insert / n_ops << " microseconds/insert (spsi)" << endl;
   cout << (double)sec_spsi_remove / n_ops << " microseconds/remove (spsi)" << endl;
   cout << (double)sec_insert_2 / n_ops << " microseconds/insert2 (spsi)" << endl;

   cout << "Size of spsi: " << sp.size() << endl;
   cout << "Bitsize of spsi: " << sp.bit_size() << endl;
   cout << "sum (spsi): " << sp.psum() << endl;

   return 0;
}
