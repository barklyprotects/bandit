#include <specs/specs.h>

using namespace bandit::fakes;

go_bandit([](){

  describe("describe:", [](){
    bandit::detail::voidfunc_t describe_fn;
    fake_reporter_ptr reporter;

    before_each([&](){
      reporter = fake_reporter_ptr(new fake_reporter());
    });


    auto call_describe = [&](){
        describe("something", describe_fn, *(reporter.get()));
    };

    describe("with a succeeding 'it'", [&](){

      before_each([&](){
        describe_fn = [](){};
      });

      it("tells reporter it's starting a run", [&](){
        call_describe();
        AssertThat(reporter->call_log(), Has().Exactly(1).EqualTo("context_starting: something"));
      });

      it("tells reporter it's finished a run", [&](){
        call_describe();
        AssertThat(reporter->call_log(), Has().Exactly(1).EqualTo("context_ended: something"));
      });

    });


  });

});