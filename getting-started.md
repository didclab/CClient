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

All types defined by the SDK are located in the `Onedatashare` namespace.

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
const auto credential_service {Onedatashare::Credential_service::create("MYONEDATASHARETOKEN")};
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
const auto url {credential_service->oauth_url(Onedatashare::Oauth_endpoint_type::box)};
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

credential_service->register_credential(Onedatashare::Credential_endpoint_type::sftp, cred_id, uri, &username, &secret);
```

To register a **Credential Endpoint** that doesn't use a username or a password (such as an anonymous FTP server), you can pass
`nullptr` for `username` and `secret`.
```
const auto cred_id {"my new ftp endpoint"}; // the credential id you want to use for your new endpoint
const auto uri {"ftp://127.0.0.1:21"}; // the uri of your endpoint

credential_service->register_credential(Onedatashare::Credential_endpoint_type::ftp, cred_id, uri, nullptr, nullptr);
```

Sometimes you may want to see which endpoints you have registered. This can be done with the
[`credential_id_list`](https://didclab.github.io/CClient/classOne__data__share_1_1Credential__service.html#a585932819bfece00eb685eec5f75d1ed)
method. You can use `credential_id_list` to list all of your registered **Credential Identifiers** of any endpoint type. The types that can be can use are members of the
[`Endpoint_type`](https://didclab.github.io/CClient/namespaceOne__data__share.html#afd0bef6eb16235b5251e388dfe40d59d)
enumeration.
```
const auto list {credential_service->credential_id_list(Onedatashare::Endpoint_type::sftp)};

for (const auto& id : list) {
    std::cout << id << std::endl;
}
```

Accessing Endpoints
-------------------
Now that you have an endpoint registered with OneDataShare, you can use OneDataShare to interact with the endpoint's contents. If you are not interested in how to list, create, remove, or download resources on an endpoint, feel free to skip to
[Making Transfers](#making-transfers).

Filesystem operations are done through the
[`Endpoint`](https://didclab.github.io/CClient/classOne__data__share_1_1Endpoint.html)
class. An `Endpoint` can be instantiated with its
[`create`](https://didclab.github.io/CClient/classOne__data__share_1_1Endpoint.html#a38f1dfd77411d4235341de8393c76e38)
method.
```
const auto sftp_server {Onedatashare::Endpoint::create(Onedatashare::Endpoint_type::sftp, "my new sftp endpoint", "MYONEDATASHARETOKEN")};
```

All methods for filesystem operations have the idea of a **Resource Identifier**. A **Resource Identifier** is simply a
string that OneDataShare uses to find a resource on an endpoint. In most cases, this string is either the name of or the
path to a resource. However, some endpoints use ids instead of paths and names. In these cases, the
**Resource Identifier** is the id of the resource. A list of how different endpoint types specify
**Resource Identifiers** can be found in the documentation of the
[`Endpoint_type`](https://didclab.github.io/CClient/namespaceOne__data__share.html#afd0bef6eb16235b5251e388dfe40d59d)
enumeration. For the remainder of this document, it is assumed that you are using endpoints that use paths and names for
**Credential Identifiers**. If you are instead using a endpoint that uses ids, the only difference is that you must use
the resource's id instead of a path or name.

To get more information about a resource on an endpoint, you can list the resource using the
[`list`](https://didclab.github.io/CClient/classOne__data__share_1_1Endpoint.html#a16129b9e1b9d5c98df2fdc19c7dace90)
method with the path to the resource you want to list. This works for any type of resource.
```
const auto myfile {sftp_server->list("/myfile.txt")};

std::cout << myfile.size << std::endl;
```
The returned
[`Resource`](https://didclab.github.io/CClient/structOne__data__share_1_1Resource.html)
object will have different fields defined depending on what type of resource was listed and what type of endpoint the
resource is from. Be sure to check the documentation of `list` for the complete description of guarantees regarding the
fields defined in the `Resource`. To be completely safe, always check `optional` values before using them.

To create a directory, you can use the
[`mkdir`](https://didclab.github.io/CClient/classOne__data__share_1_1Endpoint.html#ad792147f4a9752e2d3f61f76a7a8e04e)
method. You must specify where to create the new directory and the name of the new directory.
```
sftp_server->mkdir("/", "mynewfolder");
```

To remove a resource, you can use the
[`remove`](https://didclab.github.io/CClient/classOne__data__share_1_1Endpoint.html#ade00b441a33f868ade0af128730bbdf7)
method. You must specify the directory containing the target resource and the name of the target resource.
```
sftp_server->remove("/", "mynewfolder");
```

To download a file, you can use the
[`download`](https://didclab.github.io/CClient/classOne__data__share_1_1Endpoint.html#a882ad3a0ed06826595f7b46c3b360064)
method. You must specify the directory contianing the target file and the name of the target file.
```
sftp_server->download("/", "myfile.txt");
```

Making Transfers
----------------
OneDataShare's primary functionality is the ability to make fast and reliable transfers between different endpoints.
OneDataShare uses interprotocol translation to ensure that transfers can be made between all endpoint types. The
[`Transfer_service`](https://didclab.github.io/CClient/classOne__data__share_1_1Transfer__service.html)
class provides all functionality related to creating and monitoring transfers. Like the other
classes discussed so far, a `Transfer_service` object is instantiated with its
[`create`](https://didclab.github.io/CClient/classOne__data__share_1_1Transfer__service.html#a85f9b956392cca3a6e5437fdb0d176bf)
method.
```
const auto transfer_service {Onedatashare::Transfer_service::create("MYONEDATASHARETOKEN)};
```

Making a transfer request requires three other objects: the `Source`, the `Destination`, and the `Transfer_options`.

A
[`Source`](https://didclab.github.io/CClient/structOne__data__share_1_1Source.html)
object indicates the endpoint to transfer from and what resources to transfer. This is done by providing
the endpoint type and **Credential Identifier** information as well as the directory to transfer from and a list of the names of
files to transfer. All transfered resources must be located in the same directory.
```
const Onedatashare::Source ftp_source {Onedatashare::Endpoint_type::ftp, "my new ftp endpoint", "/", std::vector {"file1.txt", "file2.txt}};
```

A
[`Destination`](https://didclab.github.io/CClient/structOne__data__share_1_1Destination.html)
object indicates what endpoint and directory to place the transfered files in. This is done similarly to the `Source`,
except only the endpoint information and the directory to place resources in are specified.
```
const Onedatashare::Destination sftp_destination {Onedatashare::Endpoint_type::sftp, "my new sftp endpoint", "/"};
```

The
[`Transfer_options`](https://didclab.github.io/CClient/structOne__data__share_1_1Transfer__options.html)
object is instantiated like so.
```
const Onedatashare::Transfer_options options {};
```

To make the transfer request, call the
[`transfer`](https://didclab.github.io/CClient/classOne__data__share_1_1Transfer__service.html#a559fa8dd7fc18577aea4d553218cf066)
method.
```
const auto job_id {transfer_service->transfer(ftp_source, sftp_destination, options)};
```

To view the status of a transfer, you can pass the job id returned from the `transfer` method into the
[`status`](https://didclab.github.io/CClient/classOne__data__share_1_1Transfer__service.html#aed7b9855a48fa65b196436cdf2bf6f0a)
method.
```
const auto transfer_status {transfer_service.status(job_id)};
```

Error Handling
--------------
The SDK makes some assumptions whenever you make requests to OneDataShare. It is assumed that a connection can be made to OneDataShare, that the authentication token is valid, and that OneDataShare can perform the requested operation. If these assumptions are wrong, then exceptions will be thrown. There are two types of exceptions to look out for:
[`Connection_error`](https://didclab.github.io/CClient/classOne__data__share_1_1Connection__error.html)
and
[`Unexpected_response_error`.](https://didclab.github.io/CClient/classOne__data__share_1_1Unexpected__response__error.html).

These expections can be handled the same as all other C++ exceptions.
```
try {
    // ... some code calling the sdk ...
} catch (Onedatashare::Connection_error e) {
    // ... handle exception ...
} catch (Onedatashare::Unexpected_response_error e) {
    // ... handle exception ...
}
```

In addition to the standard exception behavior, `Unexpected_response_error` defines the field `status` which indicates the http status of the unexpected response. This can sometimes be useful for debugging.

```
try {
    // ... some code calling the sdk ...
} catch (Onedatashare::Unexpected_response_error e) {
    std::cerr << e.status << std::endl;
}
```

If your error handling code is the same for both exceptions, you can instead catch the more general
[`Ods_error`](https://didclab.github.io/CClient/classOne__data__share_1_1Ods__error.html)
exception.
```
try {
    // ... some code calling the sdk ...
} catch (Onedatashare::Ods_error) {
    // ... handle exception ...
}
```