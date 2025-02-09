#include "instruction_parser.h"
#include "instruction/instruction.h"
#include <array>
#include <cstdint>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <utility>

namespace 
{
template<size_t N>
std::array<uint32_t, N> readNArgs(std::stringstream &input)
{
  std::string arg;
  std::array<uint32_t, N> res;
  for (size_t i = 0; i != N; ++i)
  {
    input >> arg;
    if (arg[0] != 'x')
      res[i] = static_cast<uint32_t>(std::stoul(arg));
    else
      res[i] = static_cast<uint32_t>(std::stoul(arg.substr(1)));
  }
  return res;
}

template<typename T, size_t N, typename Indx = std::make_index_sequence<N>>
void pushNArgs(std::vector<std::shared_ptr<hw::Instruction>>& v, std::stringstream &input) {
  auto x = readNArgs<N>(input);
  [&] <std::size_t... Is> (std::index_sequence<Is...>)
  { (v.push_back(std::make_shared<T>(std::get<Is>(x)...))); }(std::make_index_sequence<N>{});
}
} // anonymous namespace

namespace hw 
{
Binary InstructionParser::parse(std::ifstream &input) 
{
  std::vector<std::shared_ptr<Instruction>> result;
  auto p = preprocess(input);
  std::unordered_map<std::string, size_t> bb2cnt = std::move(p.second);
  std::stringstream sstr(p.first);
  std::string name;
  std::string arg;
  size_t instr_cnt = 0;
  while (sstr >> name)
  {
    Instr_t instr = str2Instr.at(name);
    ++instr_cnt;
    switch (instr) {
    case Instr_t::ADD:
    {
      pushNArgs<ADDInstr, 3>(result, sstr);
      break;
    }
    case Instr_t::SUB:
    {
      pushNArgs<SUBInstr, 3>(result, sstr);
      break;
    }
    case Instr_t::MUL:
    {
      pushNArgs<MULInstr, 3>(result, sstr);
      break;
    }
    case Instr_t::DIV:
    {
      pushNArgs<DIVInstr, 3>(result, sstr);
      break;
    }
    case Instr_t::REM:
    {
      pushNArgs<REMInstr, 3>(result, sstr);
      break;
    }
    case Instr_t::XOR:
    {
      pushNArgs<XORInstr, 3>(result, sstr);
      break;
    }
    case Instr_t::INC_NEi:
    {
      pushNArgs<INC_NEiInstr, 3>(result, sstr);
      break;
    }
    case Instr_t::SUBi:
    {
      pushNArgs<SUBiInstr, 3>(result, sstr);
      break;
    }
    case Instr_t::PUT_PIXEL:
    {
      pushNArgs<PUT_PIXELInstr, 3>(result, sstr);
      break;
    }
    case Instr_t::BR_COND:
    {
      sstr >> arg;
      auto r1 = static_cast<uint32_t>(std::stoul(arg.substr(1)));
      sstr >> arg;
      auto r2 = bb2cnt.at(arg);
      result.push_back(std::make_shared<BR_CONDInstr>(r1, r2));
      break;
    }
    case Instr_t::FLUSH:
    {
      result.push_back(std::make_shared<FLUSHInstr>());
      break;
    }
    case Instr_t::EXIT:
    {
      result.push_back(std::make_shared<EXITInstr>());
      break;
    }
    default:
      break;
    }
  }
  return {result, bb2cnt, 0, 1};
}

std::pair<std::string, std::unordered_map<std::string, size_t>> InstructionParser::preprocess(std::ifstream &input)
{
  std::unordered_map<std::string, size_t> bb2cnt;
  std::string result;
  std::string name;
  std::string arg;
  size_t instr_cnt = 0;
  while (input >> name)
  {
    if (str2Instr.find(name) == str2Instr.end())
    {
      bb2cnt.insert({name, instr_cnt});
      continue;
    }
    Instr_t instr = str2Instr.at(name);
    ++instr_cnt;
    result += name + " ";
    switch (instr) {
    case Instr_t::ADD:
    case Instr_t::SUB:
    case Instr_t::MUL:
    case Instr_t::DIV:
    case Instr_t::REM:
    case Instr_t::XOR:
    case Instr_t::INC_NEi:
    case Instr_t::SUBi:
    case Instr_t::PUT_PIXEL:
    {
      input >> arg;
      result += arg + " ";
      input >> arg;
      result += arg + " ";
      input >> arg;
      result += arg + " ";
      break;
    }
    case Instr_t::BR_COND:
    {
      input >> arg;
      result += arg + " ";
      input >> arg;
      result += arg + " ";
      break;
    }
    case Instr_t::FLUSH:
    case Instr_t::EXIT:
    {
      break;
    }
    default:
      break;
    }
  }
  return {result, bb2cnt};
}
} // namespace hw