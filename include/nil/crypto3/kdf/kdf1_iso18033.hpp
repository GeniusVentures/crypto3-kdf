//---------------------------------------------------------------------------//
// Copyright (c) 2019 Nil Foundation AG
// Copyright (c) 2019 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_KDF_KDF1_18033_HPP
#define CRYPTO3_KDF_KDF1_18033_HPP

#include <nil/crypto3/kdf/detail/kdf_iso18033/kdf_iso18033_functions.hpp>

namespace nil {
    namespace crypto3 {
        namespace kdf {
            /*!
             * @brief KDF1 from ISO 18033-2
             * @tparam Hash
             */
            template<typename Hash>
            class kdf1_18033 {
                typedef detail::kdf_iso18033_functions<Hash> policy_type;

            public:
                static void process() {
                    uint32_t counter = 0;
                    secure_vector<uint8_t> h;

                    size_t offset = 0;
                    while (offset != key_len && counter != 0xFFFFFFFF) {
                        m_hash->update(secret, secret_len);
                        m_hash->update_be(counter++);
                        m_hash->update(label, label_len);
                        m_hash->update(salt, salt_len);
                        m_hash->final(h);

                        const size_t added = std::min(h.size(), key_len - offset);
                        copy_mem(&key[offset], h.data(), added);
                        offset += added;
                    }

                    return offset;
                }

            };
        }
    }
}

#endif