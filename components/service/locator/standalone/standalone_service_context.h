/*
 * Copyright (c) 2020, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef STANDALONE_SERVICE_CONTEXT_H
#define STANDALONE_SERVICE_CONTEXT_H

#include <service_locator.h>
#include <rpc/common/endpoint/call_ep.h>
#include <rpc/direct/direct_caller.h>
#include <string>

class standalone_service_context
{
public:
    standalone_service_context(const char *sn);
    virtual ~standalone_service_context();

    void init();
    void deinit();

    rpc_session_handle open(struct rpc_caller **caller);
    void close(rpc_session_handle session_handle);

    const std::string &get_service_name() const;
    struct service_context *get_service_context();

protected:
    void set_call_ep(call_ep *ep);

    virtual void do_init() {}
    virtual void do_deinit() {}

private:

    struct rpc_session
    {
        rpc_session(struct call_ep *call_ep);
        ~rpc_session();

        struct direct_caller m_direct_caller;
        struct rpc_caller *m_rpc_caller;
    };

    std::string m_sn;
    int m_ref_count;
    struct service_context m_service_context;
    struct call_ep *m_call_ep;
};

#endif /* STANDALONE_SERVICE_CONTEXT_H */