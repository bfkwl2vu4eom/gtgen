#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "CodeAnalyzerInterface.h"
#include "CodeParserCppAst.h"
#include "FunctionInfo.h"
#include "ScopeInfo.h"

/**
 * @brief Abstract Code Parser Class
 *
 */
class FunctionAnalyzerCppAst :
  public CodeAnalyzerInterface , public std::enable_shared_from_this<CodeAnalyzerInterface> {
 public:
  explicit FunctionAnalyzerCppAst(std::shared_ptr<CodeParserCppAst> p_parser);
  ~FunctionAnalyzerCppAst() override;

  std::vector<std::shared_ptr<FunctionAttributeInterface>> GetFunctions() override;
  std::vector<ScopeInfo> GetScopes() override;
 private:
  std::shared_ptr<CodeParserCppAst> p_parser_;

  std::vector<std::shared_ptr<FunctionAttributeInterface>> Get() noexcept;
  std::vector<FunctionInfo> GetFunction() noexcept;
  std::vector<MemberFunctionInfo> GetMemberFunction() noexcept;
  template <typename T>
  std::vector<FunctionInfo> ParseFunction(const T &entity) const noexcept;
  template <typename T>
  std::vector<MemberFunctionInfo> ParseMemberFunction(const T &entity) const noexcept;

};

