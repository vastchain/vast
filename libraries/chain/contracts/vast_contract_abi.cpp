/**
 *  @file
 *  @copyright defined in vast/LICENSE.txt
 */
#include <vast/chain/contracts/vast_contract_abi.hpp>
#include <vast/chain/contracts/types.hpp>
#include <vast/chain/contracts/abi_types.hpp>
#include <vast/chain/version.hpp>

namespace vast { namespace chain { namespace contracts {

/**
 * Hisotry
 * 4.1.1: Update memo field in everipass v2 and everipay v2 to be optional
 */

static auto vast_abi_version       = 4;
static auto vast_abi_minor_version = 1;
static auto vast_abi_patch_version = 1;

version
vast_contract_abi_version() {
    return version(vast_abi_version, vast_abi_minor_version, vast_abi_patch_version);
}

abi_def
vast_contract_abi() {
    auto vast_abi = abi_def();

    vast_abi.types.push_back(type_def{"address_list", "address[]"});
    vast_abi.types.push_back(type_def{"user_id", "public_key"});
    vast_abi.types.push_back(type_def{"user_list", "public_key[]"});
    vast_abi.types.push_back(type_def{"group_key", "public_key"});
    vast_abi.types.push_back(type_def{"weight_type", "uint16"});
    vast_abi.types.push_back(type_def{"fields", "field_def[]"});
    vast_abi.types.push_back(type_def{"type_name", "string"});
    vast_abi.types.push_back(type_def{"field_name", "string"});
    vast_abi.types.push_back(type_def{"permission_name", "name"});
    vast_abi.types.push_back(type_def{"action_name", "name"});
    vast_abi.types.push_back(type_def{"domain_name", "name128"});
    vast_abi.types.push_back(type_def{"domain_key", "name128"});
    vast_abi.types.push_back(type_def{"group_name", "name128"});
    vast_abi.types.push_back(type_def{"token_name", "name128"});
    vast_abi.types.push_back(type_def{"account_name", "name128"});
    vast_abi.types.push_back(type_def{"proposal_name", "name128"});
    vast_abi.types.push_back(type_def{"fungible_name", "name128"});
    vast_abi.types.push_back(type_def{"symbol_name", "name128"});
    vast_abi.types.push_back(type_def{"symbol_id_type", "uint32"});
    vast_abi.types.push_back(type_def{"balance_type", "asset"});
    vast_abi.types.push_back(type_def{"group_def", "group"});
    vast_abi.types.push_back(type_def{"meta_key", "name128"});
    vast_abi.types.push_back(type_def{"meta_value", "string"});
    vast_abi.types.push_back(type_def{"suspend_status", "uint8"});
    vast_abi.types.push_back(type_def{"conf_key", "name128"});

    // enums def
    vast_abi.enums.emplace_back( enum_def {
        "passive_method_type", "uint8", {
            "within_amount",
            "outside_amount"
        }
    });

    vast_abi.enums.emplace_back( enum_def {
        "stake_type", "uint64", {
            "active",
            "fixed"
        }
    });

    vast_abi.enums.emplace_back( enum_def {
        "unstake_op", "uint64", {
            "propose",
            "cancel",
            "settle"
        }
    });

    // structures def
    vast_abi.structs.emplace_back( struct_def {
        "void", "", {}
    });

    vast_abi.structs.emplace_back( struct_def {
        "key_weight", "", {
            {"key", "public_key"},
            {"weight", "weight_type"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "authorizer_weight", "", {
            {"ref", "authorizer_ref"},
            {"weight", "weight_type"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "permission_def", "", {
            {"name", "permission_name"},
            {"threshold", "uint32"},
            {"authorizers", "authorizer_weight[]"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "locknft_def", "", {
            {"domain", "domain_name"},
            {"names", "token_name[]"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "lockft_def", "", {
            {"from", "address"},
            {"amount", "asset"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "lock_condkeys", "", {
            {"threshold", "uint16"},
            {"cond_keys", "public_key[]"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "dist_stack_receiver", "", {
            {"threshold", "asset"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "dist_fixed_rule", "", {
            {"receiver", "dist_receiver"},
            {"amount", "asset"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "dist_percent_rule", "", {
            {"receiver", "dist_receiver"},
            {"percent", "percent"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "dist_percent_rule_v2", "", {
            {"receiver", "dist_receiver"},
            {"percent", "percent_slim"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "passive_method", "", {
            {"action", "name"},
            {"method", "passive_method_type"}
        }
    });

    // variants def
    vast_abi.variants.emplace_back( variant_def {
        "lock_asset", {
            {"tokens", "locknft_def"},
            {"fungible", "lockft_def"}
        }
    });

    vast_abi.variants.emplace_back( variant_def {
        "lock_condition", {
            {"cond_keys", "lock_condkeys"}
        }
    });

    vast_abi.variants.emplace_back( variant_def {
        "lock_aprvdata", {
            {"cond_key", "void"}
        }
    });

    vast_abi.variants.emplace_back( variant_def {
        "dist_receiver", {
            {"address", "address"},
            {"ftholders", "dist_stack_receiver"}
        }
    });

    vast_abi.variants.emplace_back( variant_def {
        "dist_rule", {
            {"fixed", "dist_fixed_rule"},
            {"percent", "dist_percent_rule"},
            {"remaining_percent", "dist_percent_rule"}
        }
    });

    vast_abi.variants.emplace_back( variant_def {
        "dist_rule_v2", {
            {"fixed", "dist_fixed_rule"},
            {"percent", "dist_percent_rule_v2"},
            {"remaining_percent", "dist_percent_rule_v2"}
        }
    });

    // actions def
    vast_abi.structs.emplace_back( struct_def {
        "newdomain", "", {
            {"name", "domain_name"},
            {"creator", "user_id"},
            {"issue", "permission_def"},
            {"transfer", "permission_def"},
            {"manage", "permission_def"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "issuetoken", "", {
            {"domain", "domain_name"},
            {"names", "token_name[]"},
            {"owner", "address_list"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "transfer", "", {
            {"domain", "domain_name"},
            {"name", "token_name"},
            {"to", "address_list"},
            {"memo", "string"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "destroytoken", "", {
            {"domain", "domain_name"},
            {"name", "token_name"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "newgroup", "", {
            {"name", "group_name"},
            {"group", "group_def"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "updategroup", "", {
            {"name", "group_name"},
            {"group", "group_def"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "updatedomain", "", {
            {"name", "domain_name"},
            {"issue", "permission_def?"},
            {"transfer", "permission_def?"},
            {"manage", "permission_def?"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "newfungible", "", {
            {"name", "fungible_name"},
            {"sym_name", "symbol_name"},
            {"sym", "symbol"},
            {"creator", "user_id"},
            {"issue", "permission_def"},
            {"manage", "permission_def"},
            {"total_supply", "asset"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "newfungible_v2", "", {
            {"name", "fungible_name"},
            {"sym_name", "symbol_name"},
            {"sym", "symbol"},
            {"creator", "user_id"},
            {"issue", "permission_def"},
            {"transfer", "permission_def"},
            {"manage", "permission_def"},
            {"total_supply", "asset"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "updfungible", "", {
            {"sym_id", "symbol_id_type"},
            {"issue", "permission_def?"},
            {"manage", "permission_def?"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "updfungible_v2", "", {
            {"sym_id", "symbol_id_type"},
            {"issue", "permission_def?"},
            {"transfer", "permission_def?"},
            {"manage", "permission_def?"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "issuefungible", "", {
            {"address", "address"},
            {"number", "asset"},
            {"memo", "string"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "transferft", "", {
            {"from", "address"},
            {"to", "address"},
            {"number", "asset"},
            {"memo", "string"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "recycleft", "", {
            {"address", "address"},
            {"number", "asset"},
            {"memo", "string"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "destroyft", "", {
            {"address", "address"},
            {"number", "asset"},
            {"memo", "string"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "vast2pvast", "", {
            {"from", "address"},
            {"to", "address"},
            {"number", "asset"},
            {"memo", "string"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "addmeta", "", {
            {"key", "meta_key"},
            {"value", "meta_value"},
            {"creator", "authorizer_ref"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "newsuspend", "", {
            {"name", "proposal_name"},
            {"proposer", "user_id"},
            {"trx", "transaction"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "cancelsuspend", "", {
            {"name", "proposal_name"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "aprvsuspend", "", {
            {"name", "proposal_name"},
            {"signatures", "signature[]"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "execsuspend", "", {
           {"name", "proposal_name"},
           {"executor", "user_id"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "paycharge", "", {
           {"payer", "address"},
           {"charge", "uint32"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "paybonus", "", {
           {"payer", "address"},
           {"amount", "asset"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "everipass", "", {
           {"link", "vast_link"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "everipass_v2", "", {
           {"link", "vast_link"},
           {"memo", "string?"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "everipay", "", {
           {"link", "vast_link"},
           {"payee", "address"},
           {"number", "asset"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "everipay_v2", "", {
           {"link", "vast_link"},
           {"payee", "address"},
           {"number", "asset"},
           {"memo", "string?"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "prodvote", "", {
           {"producer", "account_name"},
           {"key", "conf_key"},
           {"value", "int64"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "producer_key", "", {
           {"producer_name", "account_name"},
           {"block_signing_key", "public_key"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "updsched", "", {
           {"producers", "producer_key[]"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "newlock", "", {
            {"name", "proposal_name"},
            {"proposer", "user_id"},
            {"unlock_time", "time_point_sec"},
            {"deadline","time_point_sec"},
            {"assets","lock_asset[]"},
            {"condition", "lock_condition"},
            {"succeed", "address[]"},
            {"failed", "address[]"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "aprvlock", "", {
            {"name", "proposal_name"},
            {"approver", "user_id"},
            {"data", "lock_aprvdata"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "tryunlock", "", {
           {"name", "proposal_name"},
           {"executor", "user_id"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "setpsvbonus", "", {
           {"sym", "symbol"},
           {"rate", "percent"},
           {"base_charge", "asset"},
           {"charge_threshold", "asset?"},
           {"minimum_charge", "asset?"},
           {"dist_threshold", "asset"},
           {"rules", "dist_rule[]"},
           {"methods", "passive_method[]"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "setpsvbonus_v2", "", {
           {"sym_id", "symbol_id_type"},
           {"rate", "percent_slim"},
           {"base_charge", "asset"},
           {"charge_threshold", "asset?"},
           {"minimum_charge", "asset?"},
           {"dist_threshold", "asset"},
           {"rules", "dist_rule_v2[]"},
           {"methods", "passive_method[]"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "distpsvbonus", "", {
           {"sym_id", "symbol_id_type"},
           {"deadline", "time_point"},
           {"final_receiver", "address?"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "newstakepool", "", {
           {"sym_id", "symbol_id_type"},
           {"purchase_threshold", "asset"},
           {"demand_r", "int32"},
           {"demand_t", "int32"},
           {"demand_q", "int32"},
           {"demand_w", "int32"},
           {"fixed_r", "int32"},
           {"fixed_t", "int32"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "updstakepool", "", {
           {"sym_id", "symbol_id_type"},
           {"purchase_threshold", "asset?"},
           {"demand_r", "int32?"},
           {"demand_t", "int32?"},
           {"demand_q", "int32?"},
           {"demand_w", "int32?"},
           {"fixed_r", "int32?"},
           {"fixed_t", "int32?"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "newvalidator", "", {
           {"name", "account_name"},
           {"creator", "user_id"},
           {"signer", "public_key"},
           {"withdraw", "permission_def"},
           {"manage", "permission_def"},
           {"commission", "percent_slim"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "staketkns", "", {
           {"staker", "user_id"},
           {"validator", "account_name"},
           {"amount", "asset"},
           {"type", "stake_type"},
           {"fixed_days", "int32"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "unstaketkns", "", {
           {"staker", "user_id"},
           {"validator", "account_name"},
           {"units", "int64"},
           {"sym_id", "symbol_id_type"},
           {"op", "unstake_op"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "toactivetkns", "", {
           {"staker", "user_id"},
           {"validator", "account_name"},
           {"sym_id", "symbol_id_type"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "valiwithdraw", "", {
           {"name", "account_name"},
           {"addr", "address"},
           {"amount", "asset"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "recvstkbonus", "", {
           {"validator", "account_name"},
           {"sym_id", "symbol_id_type"}
        }
    });

    // abi_def fields
    vast_abi.structs.emplace_back( struct_def {
        "field_def", "", {
            {"name", "field_name"},
            {"type", "type_name"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "struct_def", "", {
            {"name", "type_name"},
            {"base", "type_name"},
            {"fields", "fields"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "type_def", "", {
            {"new_type_name", "type_name"},
            {"type", "type_name"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "action_def", "", {
           {"name", "action_name"},
           {"type", "type_name"}
        }
    });

    // blocks & transactions def
    vast_abi.structs.emplace_back( struct_def {
        "action", "", {
            {"name", "action_name"},
            {"domain", "domain_name"},
            {"key", "domain_key"},
            {"data", "bytes"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "transaction_header", "", {
            {"expiration", "time_point_sec"},
            {"ref_block_num", "uint16"},
            {"ref_block_prefix", "uint32"},
            {"max_charge", "uint32"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "transaction", "transaction_header", {
            {"actions", "action[]"},
            {"payer", "address"},
            {"transaction_extensions", "extensions"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "signed_transaction", "transaction", {
            {"signatures", "signature[]"}
        }
    });

    vast_abi.structs.emplace_back( struct_def {
        "block_header", "", {
            {"previous", "checksum256"},
            {"timestamp", "uint32"},
            {"transaction_mroot", "checksum256"},
            {"action_mroot", "checksum256"},
            {"block_mroot", "checksum256"},
            {"producer", "account_name"},
            {"schedule_version", "uint32"},
            {"new_producers", "producer_schedule?"}
        }
    });

    return vast_abi;
}

}}}  // namespace vast::chain::contracts