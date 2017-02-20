#ifndef LIBDERP_DERPEXCEPT_HPP
#define LIBDERP_DERPEXCEPT_HPP


#ifdef LIBDERP_NO_EXCEPT

#include <iostream>
#define LIBDERP_EXCEPT(err) std::cerr << "Error: " << err << endl; abort();

#else

#include <stdexcept>
#define LIBDERP_EXCEPT(err) throw std::runtime_error(err);

#endif


#endif //LIBDERP_DERPEXCEPT_HPP
