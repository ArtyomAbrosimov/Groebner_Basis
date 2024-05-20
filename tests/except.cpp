#include <iostream>
#include <exception>
#include <stdexcept>
#include "except.h"

namespace except {
    void React() {
        try {
            throw;
        } catch (const std::runtime_error &e) {
            std::cerr << "Caught a runtime_error: " << e.what() << "\n";
        } catch (const std::range_error &e) {
            std::cerr << "Caught a range_error: " << e.what() << "\n";
        } catch (const std::overflow_error &e) {
            std::cerr << "Caught an overflow_error: " << e.what() << "\n";
        } catch (const std::underflow_error &e) {
            std::cerr << "Caught an underflow_error: " << e.what() << "\n";
        } catch (const std::logic_error &e) {
            std::cerr << "Caught a logic_error: " << e.what() << "\n";
        } catch (const std::domain_error &e) {
            std::cerr << "Caught a domain_error: " << e.what() << "\n";
        } catch (const std::invalid_argument &e) {
            std::cerr << "Caught an invalid_argument: " << e.what() << "\n";
        } catch (const std::length_error &e) {
            std::cerr << "Caught a length_error: " << e.what() << "\n";
        } catch (const std::out_of_range &e) {
            std::cerr << "Caught an out_of_range: " << e.what() << "\n";
        } catch (...) {
            std::cerr << "Caught an unknown exception." << "\n";
        }
    }
}
