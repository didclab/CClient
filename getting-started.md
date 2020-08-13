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

OneDataShare provides a uniform interface for accessing and transfering files between different endpoints. The SDK
allows users to:
- Register endpoints with OneDataShare.
- See which endpoints are registered.
- View contents of endpoints.
- Create directories on endpoints.
- Remove files and directories from endpoints.
- Directly download files from endpoints.
- Efficiently transfer files between endpoints.
- Monitor status of ongoing transfers.

Including the header file `onedatashare.h` will import all other headers required to use the SDK. This is the
recommended approach, although including each header file individually is also supported.

The API of the SDK is exposed through three primary classes: `Credential_service`, `Endpoint`, and `Transfer_service`.
Each class has a static `create` method that returns a new instance of the class. For all three classes, the `create`
method requires a OneDataShare authentication token which must be obtained from the
[OneDataShare website](https://www.onedatashare.org/).

All classes and structs defined by the SDK are located in the `Onedatashare` namespace.

For installation and CMake integration instructions, see the
[GitHub repository](https://github.com/didclab/CClient).
Be sure to reference the
[documentation](https://didclab.github.io/CClient)
as you go through this tutorial.

Registering Credentials
-----------------------

OneDataShare's primary goal is to provide a uniform interface for making efficient and reliable transfers between
different endpoints. To take advantage of this functionality, it is first necessary to have endpoints registered with
OneDataShare. The SDK provides this functionality through the
[`Credential_service`](https://didclab.github.io/CClient/classOne__data__share_1_1Credential__service.html)
class. A `Credential_service` object can be instantiated by calling its
[`create`](https://didclab.github.io/CClient/classOne__data__share_1_1Credential__service.html#a35d157e76a51329e44cea9df8c06c355)
method like so:
```
const auto credential_service {Onedatashare::Credential_service::create("YOURONEDATASHARETOKEN")};
```

`Credential_service::create`'s sole argument is the OneDataShare authentication token obtained from the OneDataShare website.

Before using the new `Credential_service` object, there are a few points to be aware of. The endpoint types supported by
OneDataShare can be divided into two categories: **OAuth Endpoints** and **Credential Endpoints**. In the SDK, these
two sets of endpoint types are indicated by the
[`Oauth_endpoint_type`](https://didclab.github.io/CClient/namespaceOne__data__share.html#a638c03654eebf7030e7e5318f5ef0040)
and
[`Credential_endpoint_type`](https://didclab.github.io/CClient/namespaceOne__data__share.html#a8a22739a674b139dbcc385b50e2ab21a)
enumerations respectively. **OAuth Endpoints** are registered by visiting a URL provided by the endpoint type in which
you log into the endpoint and give OneDataShare permission to use the endpoint. **Credential Endpoints** are
registered by giving the endpoint's credentials to OneDataShare directly. One other note is the idea of
**Credential Identifiers**. These are strings associated with a specific endpoint registered on your account.
For **Oauth Endpoints**, the **Credential Identifier** is set automatically as the email of the account used to log into the endpoint. For
**Credential Endpoints**, the **Credential Identifer** is specified as part of uploading credentials to OneDataShare.
The **Credential Identifier** of an endpoint is used to refer to that endpoint when interacting with it through OneDataShare.

To register an **OAuth Endpoint**, first use the
[`oauth_url`](https://didclab.github.io/CClient/classOne__data__share_1_1Credential__service.html#a83e81a11a3f1731958a5d11cd48163ca)
method.
```
const auto url {credential_service.oauth_url(Onedatashare::Oauth_endpoint_type::box)};
```
This method returns the URL you must visit to register an endpoint of the specified type.

To register a **Credential Endpoint**, you can use the
[`register_credential`](https://didclab.github.io/CClient/classOne__data__share_1_1Credential__service.html#ae33eda8a7474eb664c74ca7cb3abd39b)
method.
```
const auto cred_id {"my new sftp endpoint"}; // the credential id you want to use for your new endpoint
const auto uri {"sftp://127.0.0.1:22"}; // the uri of your endpoint
const std::string username {"foo"}; // your username for the endpoint
const std::string secret {"bar"}; // your password for the endpoint

credential_service.register_credential(Onedatashare::Credential_endpoint_type::sftp, cred_id, uri, &username, &secret);
```

To register a **Credential Endpoint** that doesn't use a username or a password (such as an anonymous FTP server), you can pass
`nullptr` for `username` and `secret`.
```
const auto cred_id {"my new ftp endpoint"}; // the credential id you want to use for your new endpoint
const auto uri {"ftp://127.0.0.1:21"}; // the uri of your endpoint

credential_service.register_credential(Onedatashare::Credential_endpoint_type::ftp, cred_id, uri, nullptr, nullptr);
```

Sometimes you may want to see which endpoints you have registered. This can be done with the
[`credential_id_list`](https://didclab.github.io/CClient/classOne__data__share_1_1Credential__service.html#a585932819bfece00eb685eec5f75d1ed)
method. You can use `credential_id_list` to list all of the registered **Credential Identifiers** of any endpoint type. The types you can use are members of the
[`Endpoint_type`](https://didclab.github.io/CClient/namespaceOne__data__share.html#afd0bef6eb16235b5251e388dfe40d59d)
enumeration.
```
const auto list {credential_service.credential_id_list(Onedatashare::Endpoint_type::sftp)};

for (const auto& id : list) {
    std::cout << id << std::endl;
}
```

Accessing Endpoints
-------------------



Making Transfers
----------------



Error Handling
--------------


