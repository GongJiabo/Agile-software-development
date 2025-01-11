#include "../utility/Date.h"
#include "../utility/Employee.h"
#include "../utility/PayCheck.h"
#include "../utility/PayrollDatabase.h"
#include "../utility/ServiceCharge.h"
#include "../affiliation/NoAffiliation.h"
#include "../affiliation/UnionAffiliation.h"
#include "../classification/CommissionedClassification.h"
#include "../classification/HourlyClassification.h"
#include "../classification/PaymentClassification.h"
#include "../classification/SalariedClassification.h"
#include "../paymentmethod/HoldMethod.h"
#include "../paymentmethod/DirectMethod.h"
#include "../paymentmethod/MailMethod.h"
#include "../schedule/BiweeklySchedule.h"
#include "../schedule/MonthlySchedule.h"
#include "../schedule/WeeklySchedule.h"
#include "../transactions/AddCommissionedEmployee.h"
#include "../transactions/AddHourlyEmployee.h"
#include "../transactions/AddSalariedEmployee.h"
#include "../transactions/ChangeAddressTransaction.h"
#include "../transactions/ChangeCommissionedTransaction.h"
#include "../transactions/ChangeDirectMethodTransaction.h"
#include "../transactions/ChangeNameTransaction.h"
#include "../transactions/ChangeHourlyTransaction.h"
#include "../transactions/ChangeHoldMethodTransaction.h"
#include "../transactions/ChangeMailMethodTransaction.h"
#include "../transactions/ChangeMemberTransaction.h"
#include "../transactions/ChangeSalariedTransaction.h"
#include "../transactions/ChangeUnaffiliatedTransaction.h"
#include "../transactions/DeleteEmployeeTransaction.h"
#include "../transactions/PaydayTransaction.h"
#include "../transactions/SalesReceiptTransaction.h"
#include "../transactions/ServiceChargeTransaction.h"
#include "../transactions/TimeCardTransaction.h"
#include "../third_party/googletest/googletest/include/gtest/gtest.h"
#include <cassert>
#include <string>
#include <iostream>

extern PayrollDatabase GpayrollDatabase;

void ValidatePaycheck(PaydayTransaction& pt, int empId, double pay,
                      const Date& payDate)
{
    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_TRUE(pc);
    ASSERT_EQ(payDate, pc->GetPayPeriodEndDate());
    ASSERT_EQ(std::string("Hold"), pc->GetField("Disposition"));
    ASSERT_DOUBLE_EQ(pay, pc->GetGrossPay());
    ASSERT_DOUBLE_EQ(0, pc->GetDeductions());
    ASSERT_DOUBLE_EQ(pay, pc->GetNetPay());
}

TEST(PayrollTest, TestAddSalariedEmployee)
{
    int empID = 1;
    AddSalariedEmployee t(empID, "Bob", "Home", 1000.00);
    t.Execute();

    Employee* e = GpayrollDatabase.GetEmployee(empID);
    ASSERT_TRUE("Bob" == e->GetName());

    PaymentClassification* pc = e->GetClassification();
    SalariedClassification* sc = dynamic_cast<SalariedClassification*>(pc);
    ASSERT_TRUE(sc);
    ASSERT_EQ(1000.00, sc->GetSalary());

    PaymentSchedule* ps = e->GetSchedule();
    MonthlySchedule* ms = dynamic_cast<MonthlySchedule*>(ps);
    ASSERT_TRUE(ms);

    PaymentMethod* pm = e->GetMethod();
    HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
    ASSERT_TRUE(hm);
}

TEST(PayrollTest, TestAddHourlyEmployee)
{
    int empId = 2;
    AddHourlyEmployee addHourlyEmployee(empId, "Bob", "Home", 80.0);
    addHourlyEmployee.Execute();

    Employee* e = GpayrollDatabase.GetEmployee(empId);
    ASSERT_EQ(std::string("Bob"), e->GetName());
    ASSERT_EQ(std::string("Home"), e->GetAddress());

    PaymentClassification* pc = e->GetClassification();
    HourlyClassification* hc = dynamic_cast<HourlyClassification*>(pc);
    ASSERT_NE(nullptr, hc);

    ASSERT_DOUBLE_EQ(80.0, hc->GetHourlyRate());

    PaymentSchedule* ps = e->GetSchedule();
    WeeklySchedule* ws = dynamic_cast<WeeklySchedule*>(ps);
    ASSERT_NE(nullptr, ws);

    PaymentMethod* pm = e->GetMethod();
    HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
    ASSERT_NE(nullptr, hm);
}

TEST(PayrollTest, TestAddCommissionedEmployee)
{
    int empId = 3;
    AddCommissionedEmployee addCommissionedEmployee(empId, "Carl", "Home",
                                                    1000.0, 0.2);
    addCommissionedEmployee.Execute();

    Employee* e = GpayrollDatabase.GetEmployee(empId);
    ASSERT_EQ(std::string("Carl"), e->GetName());
    ASSERT_EQ(std::string("Home"), e->GetAddress());

    PaymentClassification* pc = e->GetClassification();
    CommissionedClassification* cc =
        dynamic_cast<CommissionedClassification*>(pc);
    ASSERT_NE(nullptr, cc);

    ASSERT_DOUBLE_EQ(1000.0, cc->GetSalary());
    ASSERT_DOUBLE_EQ(0.2, cc->GetCommissionRate());

    PaymentSchedule* ps = e->GetSchedule();
    BiweeklySchedule* ws = dynamic_cast<BiweeklySchedule*>(ps);
    ASSERT_NE(nullptr, ws);

    PaymentMethod* pm = e->GetMethod();
    HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
    ASSERT_NE(nullptr, hm);
}

TEST(PayrollTest, TestDeleteEmplyee)
{
    int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    Employee* e = GpayrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);

    DeleteEmployeeTransaction dt(empId);
    dt.Execute();
    Employee* de = GpayrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(de == nullptr);
}

TEST(PayrollTest, TestTimeCardTransaction)
{
    int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();

    TimeCardTransaction tct(Date(10, 31, 2001), 8.0, empId);
    tct.Execute();

    Employee* e = GpayrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);

    PaymentClassification* pc = e->GetClassification();
    HourlyClassification* hc = dynamic_cast<HourlyClassification*>(pc);
    ASSERT_TRUE(hc);

    TimeCard* tc = hc->GetTimeCard(Date(10, 31, 2001));
    ASSERT_TRUE(tc);
    ASSERT_EQ(8.0, tc->GetHours());
}

TEST(PayrollTest, TestAddSalesReceipt)
{
    int empId = 6;
    AddCommissionedEmployee add(empId, "Jack", "CA", 800.0, 0.2);
    add.Execute();

    Date date(4, 6, 2017);
    SalesReceiptTransaction srt(date, 15, empId);
    srt.Execute();

    Employee* e = GpayrollDatabase.GetEmployee(empId);
    ASSERT_NE(nullptr, e);

    PaymentClassification* pc = e->GetClassification();
    ASSERT_NE(nullptr, pc);
    CommissionedClassification* cc =
        dynamic_cast<CommissionedClassification*>(pc);
    ASSERT_NE(nullptr, cc);

    SalesReceipt* sr = cc->GetSalesReceipt(date);
    ASSERT_NE(nullptr, sr);
    ASSERT_DOUBLE_EQ(15, sr->GetAmount());
}

TEST(PayrollTest, TestAddServiceCharge)
{
    int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();

    Employee* e = GpayrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);

    int memberId = 86; // Maxell Smart
    UnionAffiliation* af = new UnionAffiliation(memberId, 12.5);
    e->SetAffiliation(af);
    GpayrollDatabase.AddUnionMember(memberId, e);

    ServiceChargeTransaction sct(memberId, Date(20011101), 12.95);
    sct.Execute();

    ServiceCharge* sc = af->GetServiceCharge(Date(20011101));
    ASSERT_TRUE(sc);
    ASSERT_EQ(12.95, sc->GetAmount());
}

TEST(PayrollTest, TestChangeNameTransaction)
{
    int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeNameTransaction cnt(empId, "Bob");
    cnt.Execute();
    Employee* e = GpayrollDatabase.GetEmployee(empId);
    assert(e);
    assert("Bob" == e->GetName());
}

TEST(PayrollTest, TestChangeEmployeeAddress)
{
    int empId = 9;

    AddSalariedEmployee a = AddSalariedEmployee(empId, "Marc", "Home", 1000);
    a.Execute();

    std::string address = "Joel";
    ChangeAddressTransaction cat = ChangeAddressTransaction(empId, address);
    cat.Execute();

    Employee* e = GpayrollDatabase.GetEmployee(empId);
    ASSERT_EQ(address, e->GetAddress());
}

TEST(PayrollTest, TestChangeHourlyTransaction)
{
    int empId = 10;

    AddSalariedEmployee a(empId, "Bob", "Home", 1000);
    a.Execute();

    ChangeHourlyTransaction cht(empId, 20.0);
    cht.Execute();

    Employee* e = GpayrollDatabase.GetEmployee(empId);
    PaymentClassification* pc = e->GetClassification();
    ASSERT_NE(nullptr, pc);
    HourlyClassification* hc = dynamic_cast<HourlyClassification*>(pc);
    ASSERT_NE(nullptr, hc);
    ASSERT_EQ(20.0, hc->GetHourlyRate());
    PaymentSchedule* ps = e->GetSchedule();
    ASSERT_NE(nullptr, ps);
    WeeklySchedule* ws = dynamic_cast<WeeklySchedule*>(ps);
    ASSERT_NE(nullptr, ws);
}

TEST(PayrollTest, TestChangeSalariedTransaction)
{
    int empId = 11;

    AddHourlyEmployee a(empId, "Bob", "Home", 20);
    a.Execute();

    ChangeSalariedTransaction cst(empId, 1000);
    cst.Execute();

    Employee* e = GpayrollDatabase.GetEmployee(empId);
    PaymentClassification* pc = e->GetClassification();
    ASSERT_NE(nullptr, pc);
    SalariedClassification* sc = dynamic_cast<SalariedClassification*>(pc);
    ASSERT_NE(nullptr, sc);
    ASSERT_DOUBLE_EQ(1000, sc->GetSalary());
    PaymentSchedule* ps = e->GetSchedule();
    ASSERT_NE(nullptr, ps);
    MonthlySchedule* ms = dynamic_cast<MonthlySchedule*>(ps);
    ASSERT_NE(nullptr, ms);
}

TEST(PayrollTest, TestChangeCommissionedTransaction)
{
    int empId = 12;
    AddHourlyEmployee a(empId, "Bob", "Home", 20);
    a.Execute();

    ChangeCommissionedTransaction cct(empId, 1000, 0.2);
    cct.Execute();

    Employee* e = GpayrollDatabase.GetEmployee(empId);
    PaymentClassification* pc = e->GetClassification();
    ASSERT_NE(nullptr, pc);
    CommissionedClassification* cc =
        dynamic_cast<CommissionedClassification*>(pc);
    ASSERT_NE(nullptr, cc);
    ASSERT_DOUBLE_EQ(1000, cc->GetSalary());
    ASSERT_DOUBLE_EQ(0.2, cc->GetCommissionRate());
    PaymentSchedule* ps = e->GetSchedule();
    ASSERT_NE(nullptr, ps);
    BiweeklySchedule* ms = dynamic_cast<BiweeklySchedule*>(ps);
    ASSERT_NE(nullptr, ms);
}

TEST(PayrollTest, TestChangeMethodTransaction)
{
    int empId = 13;
    AddHourlyEmployee a(empId, "Bob", "Home", 20);
    a.Execute();

    ChangeDirectMethodTransaction cdmt(empId, "Bank1", "b112233");
    cdmt.Execute();
    Employee* e = GpayrollDatabase.GetEmployee(empId);
    PaymentMethod* pm = e->GetMethod();
    ASSERT_NE(nullptr, pm);
    DirectMethod* dm = dynamic_cast<DirectMethod*>(pm);
    ASSERT_NE(nullptr, dm);
    ASSERT_EQ(std::string("Bank1"), dm->GetBank());
    ASSERT_EQ(std::string("b112233"), dm->GetAccount());

    ChangeMailMethodTransaction cmmt(empId, std::string("Home1"));
    cmmt.Execute();
    e = GpayrollDatabase.GetEmployee(empId);
    pm = e->GetMethod();
    ASSERT_NE(nullptr, pm);
    MailMethod* mm = dynamic_cast<MailMethod*>(pm);
    ASSERT_NE(nullptr, mm);
    ASSERT_EQ(std::string("Home1"), mm->GetAddress());

    ChangeHoldMethodTransaction chmt(empId);
    chmt.Execute();
    e = GpayrollDatabase.GetEmployee(empId);
    pm = e->GetMethod();
    ASSERT_NE(nullptr, pm);
    HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
    ASSERT_NE(nullptr, hm);
}

TEST(PayrollTest, TestChangeAffiliation)
{
    int empId = 14;
    int memberId = 7752;

    AddHourlyEmployee a(empId, "Bill", "Home", 15.25);
    a.Execute();
    ChangeMemberTransaction cmt(empId, memberId, 99.42);
    cmt.Execute();

    Employee* e = GpayrollDatabase.GetEmployee(empId);
    ASSERT_NE(nullptr, e);
    Affiliation* af = e->GetAffiliation();
    ASSERT_NE(nullptr, af);
    UnionAffiliation* uaf = dynamic_cast<UnionAffiliation*>(af);
    ASSERT_NE(nullptr, uaf);
    ASSERT_DOUBLE_EQ(99.42, uaf->GetDues());

    Employee* member = GpayrollDatabase.GetUnionMember(memberId);
    ASSERT_EQ(member, e);

    ChangeUnaffiliatedTransaction cut(empId);
    cut.Execute();

    e = GpayrollDatabase.GetEmployee(empId);
    ASSERT_NE(nullptr, e);
    af = e->GetAffiliation();
    ASSERT_NE(nullptr, af);
    NoAffiliation* naf = dynamic_cast<NoAffiliation*>(af);
    ASSERT_NE(nullptr, naf);

    member = GpayrollDatabase.GetUnionMember(memberId);
    ASSERT_EQ(nullptr, member);
}

TEST(PayrollTest, TestPaySingleSalariedEmployee)
{
    int empId = 1;
    AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
    t.Execute();
    Date payDate(11, 30, 2001);
    PaydayTransaction pt(payDate);
    pt.Execute();
    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_TRUE(pc);
    ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
    ASSERT_EQ(1000.00, pc->GetGrossPay());
    ASSERT_EQ("Hold", pc->GetField("Disposition"));
    ASSERT_EQ(0.0, pc->GetDeductions());
    ASSERT_EQ(1000.0, pc->GetNetPay());
}

TEST(PayrollTest, TestPaySingleHourlyEmployeeOvertimeOneTimeCard)
{
    int empId = 19;
    AddHourlyEmployee a(empId, "Bill", "Home", 15.25);
    a.Execute();

    Date d1(4, 11, 2017);
    TimeCardTransaction tct(d1, 9, empId);
    tct.Execute();

    Date d(4, 14, 2017);
    PaydayTransaction pt(d);
    pt.Execute();
    ValidatePaycheck(pt, empId, 15.25 * (8 + 1.5), d);
}

TEST(PayrollTest, TestPaySingleSalariedEmployeeOnWrongDate)
{
    int empId = 1;
    AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
    t.Execute();
    Date payDate(11, 29, 2001);
    PaydayTransaction pt(payDate);
    pt.Execute();
    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_TRUE(pc == nullptr);
}

TEST(PayrollTest, TestPaySingleHourlyEmployeeNoTimeCards)
{
    int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    Date payDate(11, 9, 2001);
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, 0.0, payDate);
}

TEST(PayrollTest, TestPaySingleHourlyEmployeeOneTimeCard)
{
    int empId = 18;
    AddHourlyEmployee a(empId, "Bill", "Home", 15.25);
    a.Execute();

    Date d1(4, 11, 2017);
    TimeCardTransaction tct(d1, 2, empId);
    tct.Execute();

    Date d(4, 14, 2017);
    PaydayTransaction pt(d);
    pt.Execute();
    ValidatePaycheck(pt, empId, 30.5, d);
}

TEST(PayrollTest, TestPaySingleHourlyEmployeeOnWrongDate)
{
    int empId = 20;
    AddHourlyEmployee a(empId, "Bill", "Home", 15.25);
    a.Execute();

    Date d1(4, 11, 2017);
    TimeCardTransaction tct(d1, 9, empId);
    tct.Execute();

    Date d(4, 12, 2017);
    PaydayTransaction pt(d);
    pt.Execute();
    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_EQ(nullptr, pc);
}

TEST(PayrollTest, TestPaySingleHourlyEmployeeTwoTimeCards)
{
    int empId = 21;
    Date payday(4, 14, 2017);
    AddHourlyEmployee a(empId, "Bill", "Home", 15.25);
    a.Execute();

    Date d1(4, 11, 2017);
    TimeCardTransaction tct(d1, 2, empId);
    tct.Execute();

    TimeCardTransaction tct2(payday, 5, empId);
    tct2.Execute();

    PaydayTransaction pt(payday);
    pt.Execute();
    ValidatePaycheck(pt, empId, 15.25 * 7, payday);
}

TEST(PayrollTest, TestPaySingleHourlyEmployeeTwoTimeCardsSpanningTwoPayPeriod)
{
    int empId = 22;
    Date payday(4, 14, 2017);
    AddHourlyEmployee a(empId, "Bill", "Home", 15.25);
    a.Execute();

    Date d1(4, 7, 2017);
    TimeCardTransaction tct(d1, 2, empId);
    tct.Execute();

    TimeCardTransaction tct2(payday, 5, empId);
    tct2.Execute();

    PaydayTransaction pt(payday);
    pt.Execute();
    ValidatePaycheck(pt, empId, 15.25 * 5, payday);
}

TEST(PayrollTest, TestPaySingleCommissionedEmployeeNoSaleReceipt)
{
    int empId = 3;
    Date payday(4, 14, 2017);

    AddCommissionedEmployee a(empId, "Carl", "Home", 800, 40);
    a.Execute();

    PaydayTransaction pt(payday);
    pt.Execute();

    ValidatePaycheck(pt, empId, 800, payday);
}

TEST(PayrollTest, TestPaySingleCommissionedEmployeeOneSaleReceipt)
{
    int empId = 3;
    Date payday(4, 14, 2017);

    AddCommissionedEmployee a(empId, "Carl", "Home", 800, 0.2);
    a.Execute();

    SalesReceiptTransaction srt(Date(4, 13, 2017), 100, empId);
    srt.Execute();

    PaydayTransaction pt(payday);
    pt.Execute();

    ValidatePaycheck(pt, empId, 800 + 100 * 0.2, payday);
}

TEST(PayrollTest, TestPaySingleCommissionedEmployeeOnWrongDate)
{
    int empId = 3;
    Date payday(4, 13, 2017);

    AddCommissionedEmployee a(empId, "Carl", "Home", 800, 0.2);
    a.Execute();

    PaydayTransaction pt(payday);
    pt.Execute();

    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_EQ(nullptr, pc);
}

TEST(PayrollTest, TestPaySingleCommissionedEmployeeTwoSaleReceipt)
{
    int empId = 3;
    Date payday(4, 14, 2017);

    AddCommissionedEmployee a(empId, "Carl", "Home", 800, 0.2);
    a.Execute();

    SalesReceiptTransaction srt1(Date(4, 7, 2017), 100, empId);
    srt1.Execute();

    SalesReceiptTransaction srt2(payday, 150, empId);
    srt2.Execute();

    PaydayTransaction pt(payday);
    pt.Execute();

    ValidatePaycheck(pt, empId, 800 + (100 + 150) * 0.2, payday);
}

TEST(PayrollTest,
     TestPaySingleCommissionedEmployeeTwoSaleReceiptSpanningTwoPayPeriod)
{
    int empId = 3;
    Date payday(4, 14, 2017);

    AddCommissionedEmployee a(empId, "Carl", "Home", 800, 0.2);
    a.Execute();

    SalesReceiptTransaction srt1(Date(3, 31, 2017), 100, empId);
    srt1.Execute();

    SalesReceiptTransaction srt2(payday, 150, empId);
    srt2.Execute();

    PaydayTransaction pt(payday);
    pt.Execute();

    ValidatePaycheck(pt, empId, 800 + 150 * 0.2, payday);
}

TEST(PayrollTest, TestSalariedUnionMemberDues)
{
    int empId = 1;
    int membetId = 7789;
    int fridays = 4;
    AddSalariedEmployee a(empId, "Bob", "Home", 1000.0);
    a.Execute();

    ChangeMemberTransaction cmt(empId, membetId, 9.42);
    cmt.Execute();

    Date payday(4, 30, 2017);
    PaydayTransaction pt(payday);
    pt.Execute();

    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_NE(nullptr, pc);
    ASSERT_EQ(payday, pc->GetPayPeriodEndDate());
    ASSERT_EQ(std::string("Hold"), pc->GetField("Disposition"));
    ASSERT_DOUBLE_EQ(1000.0, pc->GetGrossPay());
    ASSERT_DOUBLE_EQ(9.42 * fridays, pc->GetDeductions());
    ASSERT_DOUBLE_EQ(1000.0 - 9.42 * fridays, pc->GetNetPay());
}

TEST(PayrollTest, TestHourlyUnionMemberDues)
{
    int empId = 1;
    int memberId = 7789;
    int fridays = 1;
    Date payday(4, 14, 2017);

    AddHourlyEmployee a(empId, "Bill", "Home", 15.5);
    a.Execute();

    TimeCardTransaction tct(payday, 8, empId);
    tct.Execute();

    ChangeMemberTransaction cmt(empId, memberId, 9.42);
    cmt.Execute();

    PaydayTransaction pt(payday);
    pt.Execute();

    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_NE(nullptr, pc);
    ASSERT_EQ(payday, pc->GetPayPeriodEndDate());
    ASSERT_EQ(std::string("Hold"), pc->GetField("Disposition"));
    ASSERT_DOUBLE_EQ(15.5 * 8, pc->GetGrossPay());
    ASSERT_DOUBLE_EQ(9.42 * fridays, pc->GetDeductions());
    ASSERT_DOUBLE_EQ(15.5 * 8 - 9.42 * fridays, pc->GetNetPay());
}

TEST(PayrollTest, TestCommissionedUnionMemberDues)
{
    int empId = 3;
    int memberId = 7789;
    int fridays = 2;
    Date payday(4, 14, 2017);

    AddCommissionedEmployee a(empId, "Carl", "Home", 1000, 0.2);
    a.Execute();

    SalesReceiptTransaction srt(payday, 300, empId);
    srt.Execute();

    ChangeMemberTransaction cmt(empId, memberId, 9.42);
    cmt.Execute();

    PaydayTransaction pt(payday);
    pt.Execute();

    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_NE(nullptr, pc);
    ASSERT_EQ(payday, pc->GetPayPeriodEndDate());
    ASSERT_EQ(std::string("Hold"), pc->GetField("Disposition"));
    ASSERT_DOUBLE_EQ(1000 + 300 * 0.2, pc->GetGrossPay());
    ASSERT_DOUBLE_EQ(9.42 * fridays, pc->GetDeductions());
    ASSERT_DOUBLE_EQ(1000 + 300 * 0.2 - 9.42 * fridays, pc->GetNetPay());
}

TEST(PayrollTest, TestHourlyUnionMemberServiceCharge)
{
    int empId = 1;
    int memberId = 7789;
    int fridays = 1;
    Date payday(4, 14, 2017);

    AddHourlyEmployee a(empId, "Bill", "Home", 15.5);
    a.Execute();

    TimeCardTransaction tct(payday, 8, empId);
    tct.Execute();

    ChangeMemberTransaction cmt(empId, memberId, 9.42);
    cmt.Execute();

    ServiceChargeTransaction sct(memberId, payday, 13.5);
    sct.Execute();

    PaydayTransaction pt(payday);
    pt.Execute();

    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_NE(nullptr, pc);
    ASSERT_EQ(payday, pc->GetPayPeriodEndDate());
    ASSERT_EQ(std::string("Hold"), pc->GetField("Disposition"));
    ASSERT_DOUBLE_EQ(15.5 * 8, pc->GetGrossPay());
    ASSERT_DOUBLE_EQ(9.42 * fridays + 13.5, pc->GetDeductions());
    ASSERT_DOUBLE_EQ(15.5 * 8 - (9.42 * fridays + 13.5), pc->GetNetPay());
}

TEST(PayrollTest, TestServiceChargesSpanningMultiplePayperiod)
{
    int empId = 1;
    int memberId = 7789;
    int fridays = 1;
    Date payday(4, 14, 2017);
    Date earlyDay(4, 7, 2017);
    Date lateDay(4, 21, 2017);

    AddHourlyEmployee a(empId, "Bill", "Home", 15.5);
    a.Execute();

    TimeCardTransaction tct(payday, 8, empId);
    tct.Execute();

    ChangeMemberTransaction cmt(empId, memberId, 9.42);
    cmt.Execute();

    ServiceChargeTransaction sct(memberId, payday, 13.5);
    sct.Execute();
    ServiceChargeTransaction sctEarly(memberId, earlyDay, 6.5);
    sctEarly.Execute();
    ServiceChargeTransaction sctLate(memberId, lateDay, 7.5);
    sctLate.Execute();

    PaydayTransaction pt(payday);
    pt.Execute();

    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_NE(nullptr, pc);
    ASSERT_EQ(payday, pc->GetPayPeriodEndDate());
    ASSERT_EQ(std::string("Hold"), pc->GetField("Disposition"));
    ASSERT_DOUBLE_EQ(15.5 * 8, pc->GetGrossPay());
    ASSERT_DOUBLE_EQ(9.42 * fridays + 13.5, pc->GetDeductions());
    ASSERT_DOUBLE_EQ(15.5 * 8 - (9.42 * fridays + 13.5), pc->GetNetPay());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}