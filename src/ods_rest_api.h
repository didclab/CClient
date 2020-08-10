/**
 * @file ods_rest_api.h
 * Defines namespace-global constants and functions related to the specification of the One Data Share REST API.
 *
 * @author Andrew Mikalsen
 * @date 8/10/20
 */

#ifndef ONEDATASHARE_ODS_REST_API_H
#define ONEDATASHARE_ODS_REST_API_H

namespace One_data_share {
namespace Internal {
namespace Api {

/** Path of the REST API call for oauth. */
constexpr auto oauth_path {"/api/oauth"};

/** Path of the REST API call for credentials. */
constexpr auto cred_path {"/api/cred"};

} // namespace Api
} // namespace Internal
} // namespace One_data_share

#endif // ONEDATASHARE_ODS_REST_API_H
