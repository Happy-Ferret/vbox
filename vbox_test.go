package vbox

import (
  "fmt"
  "os"
  "testing"
  //"image"
)

func TestAppVersion(t *testing.T) {
  Init()
  if err := Init(); err != nil {
    t.Fatal(err)
  }

  if AppVersion <= 4003000 {
    t.Error("AppVersion below 4.3: %d", AppVersion)
  }
}

func TestGetRevision(t *testing.T) {
  Init()
  if err := Init(); err != nil {
    t.Fatal(err)
  }

  revision, err := GetRevision()
  if err != nil {
    t.Fatal(err)
  }
  if revision <= 100000 {
    t.Error("Revision below 100000: %d", revision)
  }
}

func TestGetMachines(t *testing.T) {
  machines, err := GetMachines()
  if err != nil {
    t.Fatal(err)
  }
  if len(machines) == 0 {
    t.Error("GetMachines failed")
  }

  for _, machine := range machines {
    if err := machine.Release(); err != nil {
      t.Error(err)
    }
  }
}

func TestMain(m *testing.M) {
  if err := Init(); err != nil {
    fmt.Printf("%v\n", err)
    os.Exit(1)
  }
  result := m.Run()
  Deinit()
  os.Exit(result)
}
