// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

/**
 * @file
 * @brief Environment Credential.
 */

#pragma once

#include <azure/core/credentials/credentials.hpp>
#include <azure/core/credentials/token_credential_options.hpp>

#include <memory>

namespace Azure { namespace Identity {
  /**
   * @brief An environment credential.
   */
  class EnvironmentCredential final : public Core::Credentials::TokenCredential {
    std::unique_ptr<TokenCredential> m_credentialImpl;

  public:
    /**
     * Constructs an environment credential.
     *
     * @details May read from the following environment variables:
     * - AZURE_TENANT_ID
     * - AZURE_CLIENT_ID
     * - AZURE_CLIENT_SECRET
     * - AZURE_CLIENT_CERTIFICATE_PATH
     * - AZURE_USERNAME
     * - AZURE_PASSWORD
     */
    explicit EnvironmentCredential(
        Azure::Core::Credentials::TokenCredentialOptions options
        = Azure::Core::Credentials::TokenCredentialOptions());

    Core::Credentials::AccessToken GetToken(
        Core::Credentials::TokenRequestContext const& tokenRequestContext,
        Core::Context const& context) const override;
  };

}} // namespace Azure::Identity
