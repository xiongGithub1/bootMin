# Refresh Appl\GenData *.c / *.h timestamps to current time.
# Usage:
#   .\TouchGenData.ps1
#   .\TouchGenData.ps1 -ProjectRoot "E:\workFiles\TC367\TC367\workspace\last364"

param(
    [string]$ProjectRoot = ""
)

function Resolve-ProjectRoot {
    param([string]$Root)

    $candidates = @()
    if ($Root -ne "") {
        $candidates += (Resolve-Path -LiteralPath $Root -ErrorAction SilentlyContinue).Path
    }

    $candidates += (Get-Location).Path
    $candidates += Split-Path -Parent $PSScriptRoot
    $candidates += Split-Path -Parent (Split-Path -Parent $PSScriptRoot)

    foreach ($candidate in ($candidates | Select-Object -Unique)) {
        if ($null -eq $candidate) { continue }
        $genData = Join-Path $candidate "Appl\GenData"
        if (Test-Path -LiteralPath $genData) {
            return @{
                ProjectRoot = $candidate
                GenDataPath = $genData
            }
        }
    }

    return $null
}

$resolved = Resolve-ProjectRoot -Root $ProjectRoot
if ($null -eq $resolved) {
    Write-Error "Cannot find Appl\GenData. Pass -ProjectRoot explicitly."
    exit 1
}

$now = Get-Date
$updated = 0
$skipped = 0
$files = Get-ChildItem -Path $resolved.GenDataPath -Recurse -Include *.c,*.h -File
foreach ($file in $files) {
    if ($file.LastWriteTime.Year -eq 2024) {
        $file.LastWriteTime = $now
        $updated++
    } else {
        $skipped++
    }
}

Write-Host "TouchGenData - refresh 2024 GenData .c/.h timestamps"
Write-Host "Project root : $($resolved.ProjectRoot)"
Write-Host "GenData path : $($resolved.GenDataPath)"
Write-Host "Timestamp    : $($now.ToString('yyyy-MM-dd HH:mm:ss'))"
Write-Host "Updated      : $updated"
Write-Host "Skipped      : $skipped"
Write-Host "Done."
