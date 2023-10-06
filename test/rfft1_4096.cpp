#define BOOST_TEST_MODULE rfft1_4096
#include <boost/test/unit_test.hpp>
#include <vector>
#include <chrono>
#include "H5Cpp.h"
#include "fftw3.h"
#include "neofft.hpp"

const H5std_string DATA_NAME("data4096");
const H5std_string FFT_R_NAME("fft4096_r");
const H5std_string FFT_I_NAME("fft4096_i");

using namespace boost::unit_test;

struct local_fixture
{
    /* data */
    int argc;
    char **argv;
    std::vector<double> data_r;
    std::vector<double> fft_r;
    std::vector<double> fft_i;
    local_fixture() : argc(framework::master_test_suite().argc),
                      argv(framework::master_test_suite().argv)
    {
        data_r.resize(4096);
        fft_r.resize(4096);
        fft_i.resize(4096);
        try
        {
            H5::Exception::dontPrint();
            H5::H5File file(argv[1], H5F_ACC_RDONLY);
            H5::DataSet input_dataset = file.openDataSet(DATA_NAME);
            H5::DataSet fft_r_dataset = file.openDataSet(FFT_R_NAME);
            H5::DataSet fft_i_dataset = file.openDataSet(FFT_I_NAME);
            // read data
            H5::DataSpace dataspace = input_dataset.getSpace();
            int rank = dataspace.getSimpleExtentNdims();
            std::vector<hsize_t> dims_out(rank);
            dataspace.getSimpleExtentDims(dims_out.data(), NULL);
            H5::DataSpace mspace(rank, dims_out.data());
            input_dataset.read(data_r.data(), H5::PredType::NATIVE_DOUBLE, mspace, dataspace);
            // read data
            dataspace = fft_r_dataset.getSpace();
            rank = dataspace.getSimpleExtentNdims();
            dataspace.getSimpleExtentDims(dims_out.data(), NULL);
            mspace = H5::DataSpace(rank, dims_out.data());
            fft_r_dataset.read(fft_r.data(), H5::PredType::NATIVE_DOUBLE, mspace, dataspace);
            // read data
            dataspace = fft_i_dataset.getSpace();
            rank = dataspace.getSimpleExtentNdims();
            dataspace.getSimpleExtentDims(dims_out.data(), NULL);
            mspace = H5::DataSpace(rank, dims_out.data());
            fft_i_dataset.read(fft_i.data(), H5::PredType::NATIVE_DOUBLE, mspace, dataspace);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    };
    ~local_fixture(){};
};

BOOST_FIXTURE_TEST_SUITE(rfft_4096, local_fixture)

BOOST_AUTO_TEST_CASE(fftw_fft1_4096)
{
    auto start = std::chrono::high_resolution_clock::now();
    fftw_complex *in, *out;
    fftw_plan p;
    in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * 4096);
    out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * 4096);
    p = fftw_plan_dft_1d(4096, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    for (int i = 0; i < 4096; i++)
    {
        in[i][0] = data_r[i];
    }
    fftw_execute(p);
    auto end = std::chrono::high_resolution_clock::now();
    double dr_ms = std::chrono::duration<double, std::milli>(end - start).count();
    BOOST_TEST_MESSAGE("fftw_dft_1d: " << dr_ms << "ms");
    fftw_destroy_plan(p);
    for (int i = 0; i < 4096; i++)
    {
        BOOST_TEST_CHECK(out[i][0] - fft_r[i] < 1e-13);
        BOOST_TEST_CHECK(out[i][1] - fft_i[i] < 1e-13);
    }
    fftw_free(in);
    fftw_free(out);
}

BOOST_AUTO_TEST_CASE(neofft_fft1_4096)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::complex<double>> in(4096), out(4096);
    for (int i = 0; i < 4096; i++)
    {
        in[i] = data_r[i];
    }
    neo_dft_1d(in.data(), out.data(), 12);
    auto end = std::chrono::high_resolution_clock::now();
    double dr_ms = std::chrono::duration<double, std::milli>(end - start).count();
    BOOST_TEST_MESSAGE("neo_dft_1d: " << dr_ms << "ms");
    for (int i = 0; i < 4096; i++)
    {
        BOOST_TEST_CHECK(out[i].real() - fft_r[i] < 1e-11);
        BOOST_TEST_CHECK(out[i].imag() - fft_i[i] < 1e-11);
    }
}

BOOST_AUTO_TEST_CASE(neofft_rfft1_4096)
{
    BOOST_TEST(true /* test assertion */);
}

BOOST_AUTO_TEST_SUITE_END()