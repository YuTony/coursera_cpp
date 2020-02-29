#pragma once
#include "node.h"

using namespace std;

class Node {
   public:
    virtual bool Evaluate(const Date &date, const string &event) const = 0;
};

class EmptyNode : public Node {
   public:
    bool Evaluate(const Date &date, const string &event) const override {
        return true;
    }
};

class DateComparisonNode : public Node {
   public:
    DateComparisonNode(const Comparison cmp, const Date &date) : cmp(cmp), date_(date) {}
    bool Evaluate(const Date &date, const string &event) const override {
        switch (cmp) {
            case Comparison::Less:
                return date < date_;
                break;
            case Comparison::LessOrEqual:
                return date <= date_;
                break;
            case Comparison::Greater:
                return date > date_;
                break;
            case Comparison::GreaterOrEqual:
                return date >= date_;
                break;
            case Comparison::Equal:
                return date == date_;
                break;
            case Comparison::NotEqual:
                return date != date_;
                break;
        }
        return 0;
    }

   private:
    const Comparison cmp;
    const Date date_;
};

class EventComparisonNode : public Node {
   public:
    EventComparisonNode(const Comparison cmp, const string &event) : cmp(cmp), event_(event) {}
    bool Evaluate(const Date &date, const string &event) const override {
        switch (cmp) {
            case Comparison::Equal:
                return event == event_;
                break;
            case Comparison::NotEqual:
                return event != event_;
                break;
            case Comparison::Less:
                return event < event_;
                break;
            case Comparison::LessOrEqual:
                return event <= event_;
                break;
            case Comparison::Greater:
                return event > event_;
                break;
            case Comparison::GreaterOrEqual:
                return event >= event_;
                break;
        }
        return 0;
    }

   private:
    const Comparison cmp;
    const string event_;
};
class LogicalOperationNode : public Node {
   public:
    LogicalOperationNode(const LogicalOperation lop, shared_ptr<Node> left, shared_ptr<Node> right) : lop(lop), left_(left), right_(right) {}
    bool Evaluate(const Date &date, const string &event) const override {
        switch (lop) {
            case LogicalOperation::And:
                return left_->Evaluate(date, event) && right_->Evaluate(date, event);
                break;
            case LogicalOperation::Or:
                return left_->Evaluate(date, event) || right_->Evaluate(date, event);
                break;
        }
        return 0;
    }

   private:
    const LogicalOperation lop;
    const shared_ptr<Node> left_, right_;
};