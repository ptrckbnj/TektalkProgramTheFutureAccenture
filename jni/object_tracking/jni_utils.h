

#ifndef TENSORFLOW_EXAMPLES_ANDROID_JNI_OBJECT_TRACKING_JNI_UTILS_H_
#define TENSORFLOW_EXAMPLES_ANDROID_JNI_OBJECT_TRACKING_JNI_UTILS_H_

#include <jni.h>
#include <stdint.h>

#include "tensorflow/examples/android/jni/object_tracking/utils.h"


class JniLongField {
 public:
  JniLongField(const char* field_name)
      : field_name_(field_name), field_ID_(0) {}

  int64_t get(JNIEnv* env, jobject thiz) {
    if (field_ID_ == 0) {
      jclass cls = env->GetObjectClass(thiz);
      CHECK_ALWAYS(cls != 0, "Unable to find class");
      field_ID_ = env->GetFieldID(cls, field_name_, "J");
      CHECK_ALWAYS(field_ID_ != 0,
          "Unable to find field %s. (Check proguard cfg)", field_name_);
    }

    return env->GetLongField(thiz, field_ID_);
  }

  void set(JNIEnv* env, jobject thiz, int64_t value) {
    if (field_ID_ == 0) {
      jclass cls = env->GetObjectClass(thiz);
      CHECK_ALWAYS(cls != 0, "Unable to find class");
      field_ID_ = env->GetFieldID(cls, field_name_, "J");
      CHECK_ALWAYS(field_ID_ != 0,
          "Unable to find field %s (Check proguard cfg)", field_name_);
    }

    env->SetLongField(thiz, field_ID_, value);
  }

 private:
  const char* const field_name_;

  // This is just a cache
  jfieldID field_ID_;
};

#endif
