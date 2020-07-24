/*
 * transfer_service_impl_tests.cpp
 * Andrew Mikalsen
 * 7/23/20
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <onedatashare/ods_error.h>

#include <transfer_service_impl.h>

#include "mocks.h"

namespace {

namespace Ods = One_data_share;

class Transfer_service_impl_tests : public ::testing::Test {
};

TEST_F(Transfer_service_impl_tests, TransferThrowsConnectionErr)
{}

TEST_F(Transfer_service_impl_tests, TransferThrowsUnexpectedResponse)
{}

TEST_F(Transfer_service_impl_tests, TransferReturnsJobId)
{}

TEST_F(Transfer_service_impl_tests, StatusThrowsConnectionErr)
{}

TEST_F(Transfer_service_impl_tests, StatusBadCodeThrowsUnexpectedResponse)
{}

TEST_F(Transfer_service_impl_tests, StatusBadBodyThrowsUnexpectedResponse)
{}

TEST_F(Transfer_service_impl_tests, StatusReturnsStatus)
{}

} // namespace