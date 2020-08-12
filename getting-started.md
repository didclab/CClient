Getting Started
===============

Table of Contents
-----------------

- [Overview](#overview)
- [Registering Credentials](#registering-credentials)
- [Accessing Endpoints](#accessing-endpoints)
- [Making Transfers](#making-transfers)
- [Error Handling](#error-handling)

Overview
--------

One Data Share provides a uniform interface for accessing and transfering files between different otherwise incompatible endpoints. The SDK allows users to:
- Register endpoints with One Data Share.
- View registered endpoints.
- View contents of endpoints.
- Create directories on endpoints.
- Remove files and directories from endpoints.
- Directly download files from endpoints.
- Efficiently transfer files between endpoints.
- View status of ongoing transfers.

Including the header file `onedatashare.h` will import all other headers required to use the SDK. This is the recommended approach, though including each header file individually is also supported.

The API of the SDK is exposed through three primary class: `Credential_service`, `Endpoint`, and `Transfer_service`. Each class has a static `create` method that returns a new instance of the class. For all three classes, the `create` method requires a One Data Share authentication which must be obtained from the [One Data Share website](https://www.onedatashare.org/).

All classes and structs defined by the SDK are located in the `One_data_share` namespace.

Registering Credentials
-----------------------

One Data Share's primary goal is to provide a uniform interface for making efficient and reliable transfers between different endpoints. However, to take advantage of this functionality, it is necessary to first have endpoints registered with One Data Share. The SDK provides this functionality through the `Credential_service` class. A `Credential_service` object can be instantiated like so:
```
auto credential_service {One_data_share::Credential_service::create("YOURONEDATASHARETOKEN")};
```

The `Credential_service::create` method takes a single argument: the One Data Share authentication token to use (`"YOURONEDATASHARETOKEN"` in this example.) This method returns a `unique_ptr` to the created `Credential_service` object. The caller is expected to assume ownership of the returned value.

Before using the new `Credential_service` object, there are a few points to be aware of. The endpoint types supported by One Data Share can be divided into two categories: **OAuth Endpoints** and **Credential Endpoints**. In the SDK, these two sets of endpoint types are indicated by the `Oauth_endpoint_type` and `Credential_endpoint_type` enumerations respectively. **OAuth Endpoints** are registered by visiting a URL provided by the endpoint type in which you log into the endpoint and give One Data Share permission to use the endpoint. **Credential Endpoints** are registered by giving the endpoint's credentials to One Data Share directly. One other note is the idea of **Credential Identifiers**. These are strings that are associated with a specific endpoint registered on your account. For **Oauth Endpoints**, the **Credential Identifier** is set automatically as the email of your account. For **Credential Endpoints**, the **Credential Identifer** is specified as part of uploading credentials to One Data Share.

To register an **OAuth Endpoint**, you must use the `oauth_url` method.
```
auto url {credential_service.oauth_url(One_data_share::Oauth_endpoint_type::box)};
```
`oauth_url` returns a `string` containing the URL that can be visited to register an endpoint of the specified type. The method takes a single argument: the `Oauth_endpoint_type` indicating the endpoint type to get the URL for.

Accessing Endpoints
-------------------



Making Transfers
----------------



Error Handling
--------------


